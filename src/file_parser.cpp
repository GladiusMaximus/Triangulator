#include <vector>
#include <iostream>
#include <cmath>
#include "file_parser.h"

/******************************************************************************
  CSV iterator
******************************************************************************/

const int MAX_MAGNITUDE = 65535;
const int ELEMENTS = 380; // just an estimate
const int DATA_POINTS = 140; // just an estimate

GetLines::GetLines(const std::string& fileName, std::string* output_, char delim_) {
  file.open(fileName.c_str());
  delim = delim_;
  output = output_;
  next();
}

void GetLines::next() {
  std::string data;
  std::getline(file, data, delim);
  trim(data);
  *output = data;
}

bool GetLines::hasNext() {
  return file.good();
}

GetElements::GetElements(const std::string& text_, std::string* output_, char delim_) {
  text.str(text_);
  delim = delim_;
  output = output_;
  next();
}

void GetElements::next() {
  last = text.good(); // update status
  std::string data;
  std::getline(text, data, delim);
  trim(data);
  *output = data;
}

bool GetElements::hasNext() {
  return last; // updated the LAST time you changed values
}


std::vector<DetectionList> parseMRMData(const std::string& fileName) {
  std::vector<DetectionList> data; data.reserve(DATA_POINTS);
  std::string rowText, colText;
  long double firstTime = 0.0;
  unsigned int lineNumber = 0;
  for (GetLines row (fileName, &rowText); row.hasNext(); row.next()) {
    // Setup
    ++lineNumber;
    DetectionList line;
    GetElements col (rowText, &colText);
    //col.next() is implied by the constructor

    // Begin parsing line
    if (isdigit(colText[0])) { // first element is always timestamp (if its first char a number)
      line.timestamp = std::stold(colText); col.next();
      if (firstTime == 0.0)
        firstTime = line.timestamp;
      line.timestamp = line.timestamp - firstTime;
      std::string type;
      type = colText; col.next(); // second element is always message type
      line.messageID = std::stoi(colText); col.next(); // third element is always ID
      if (type == "MrmFullScanInfo") {
        // skip next 8
        col.next(); col.next(); col.next(); col.next(); col.next();
        col.next(); col.next(); col.next(); col.next();
        if (colText == "4") { col.next();
          col.next(); col.next(); // skip 2
          unsigned int dataLength = std::stoi(colText); col.next();
          line.rawData.reserve(dataLength);
          while (col.hasNext()) {
            double reading = fabs(std::stod(colText)); col.next();
            line.rawData.push_back(reading);
          }
          if (line.list.size() > dataLength) {
            std::cerr << "Non fatal error: Line " << lineNumber
                      << " has exceeded declared size. Expected " << dataLength
                      << ", got " << line.list.size() << "\n";
          }
        }
      } else if (type == "MrmDetectionListInfo") {
        unsigned int dataLength = std::stoi(colText); col.next();
        if (dataLength == 0)
          continue;
        line.list.reserve(dataLength);
        while (col.hasNext()) { // Then the rest of the line is data
          Detection current;
          current.index = std::stoi(colText); col.next();
          current.magnitude = std::stof(colText) / MAX_MAGNITUDE; col.next();
          line.list.push_back(current);
        }
        if (line.list.size() > dataLength) {
          std::cerr << "Non fatal error: Line " << lineNumber
                    << " has exceeded declared size. Expected " << dataLength
                    << ", got " << line.list.size() << "\n";
        }
        data.push_back(line);
      }
    }
  }
  return data;
}

void humanReadable(std::vector<DetectionList> data) {
  for (DetectionList row : data) {
    std::cout << "Row: ";
    std::cout << "Time: " << row.timestamp << ", ID: " << row.messageID;
    for (Detection elem : row.list) {
      std::cout << ", index: " << elem.index << ", magnitude: " << elem.magnitude;
    }
    std::cout << "\n";
  }
}

void pythonReadable(std::vector<DetectionList> data) {
  std::cout << "data = [\n";
  for (DetectionList row : data) {
    std::cout << "    [" << row.timestamp << ", ";
    for (Detection elem : row.list) {
      std::cout << "(" << elem.index << ", " << elem.magnitude << "), ";
    }
    std::cout << "],\n";
  }
  std::cout << "]\n";
}

void maxVal(std::vector<DetectionList> data) {
  for (DetectionList row : data) {
    Detection max;
    max.magnitude = -1.0;
    max.index = 0;
    for (Detection elem : row.list) {
      if (elem.magnitude > max.magnitude)
        max =  elem;
    }
    std::cout << row.timestamp << " " << max.index << " " << max.magnitude << "\n";
  }
}

void avgVal(std::vector<DetectionList> data) {
  for (DetectionList row : data) {
    Detection sum;
    sum.index = 0; sum.magnitude = 0.0;
    for (Detection elem : row.list) {
      sum.index += elem.index * elem.magnitude;
      sum.magnitude += elem.magnitude;
    }
    std::cout << row.timestamp << " " << sum.index / sum.magnitude << " "
              << sum.magnitude << "\n";
  }
}

/******************************************************************************
  Auxiliary functions
******************************************************************************/

// http://www.codeproject.com/Articles/10880/A-trim-implementation-for-std-string
void trim(std::string& str) {
  std::string::size_type pos = str.find_last_not_of(' ');
  if(pos != std::string::npos) {
    str.erase(pos + 1);
    pos = str.find_first_not_of(' ');
    if(pos != std::string::npos) str.erase(0, pos);
  }
  else str.erase(str.begin(), str.end());
}

