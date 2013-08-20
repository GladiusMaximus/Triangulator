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

void GetElements::skip(unsigned int howMany) {
  for (unsigned int i = 0; i < howMany; i++)
    next();
}

bool GetElements::hasNext() {
  return last; // updated the LAST time you changed values
}


std::vector<DetectionList> parseMRMData(const std::string& fileName) {
  std::vector<DetectionList> data; data.reserve(DATA_POINTS);
  std::string rowText, colText;
  unsigned int lineNumber = 0;
  for (GetLines row (fileName, &rowText); row.hasNext(); row.next()) {
    // Setup
    ++lineNumber;
    std::string rowAboveText;
    GetElements col (rowText, &colText);

    // Begin parsing line
    if (isdigit(colText[0])) {
      DetectionList line; line.lineNumber = lineNumber;
      col.skip(1); // throw away first element
      std::string type;
      type = colText; col.next(); // second element is always message type
      if (type == "MrmFullScanInfo") {
        rowAboveText = rowText;
      } else if (type == "MrmDetectionListInfo") {
        getMetaData(rowText, line);
        getDetectionList(rowText, line);
        getMotionData(rowAboveText, line);
        data.push_back(line);
      }
    }
  }
  return data;
}

void getMetaData(const std::string& rowText, DetectionList &line) {
  std::string colText;
  GetElements col (rowText, &colText);
  static long double firstTime = 0.0;

  line.timestamp = std::stold(colText); col.next(); // first element ist imestamp
  if (firstTime == 0.0)
    firstTime = line.timestamp;
  line.timestamp = line.timestamp - firstTime;
  col.next(); // throw away second element (it is the message type)
  line.messageID = std::stoi(colText); col.next(); // third element is always ID
}

void getDetectionList(const std::string& rowText, DetectionList &line) {
  std::string colText;
  GetElements col (rowText, &colText);
  col.skip(3); // we are at where the data starts

  unsigned int dataLength = std::stoi(colText); col.next();
  if (dataLength == 0)
    return;
  line.list.reserve(dataLength);
  while (col.hasNext()) { // Then the rest of the line is data
    Detection current;
    current.index = std::stoi(colText); col.next();
    current.magnitude = std::stof(colText) / MAX_MAGNITUDE; col.next();
    line.list.push_back(current);
  }
  if (line.list.size() > dataLength) {
    std::cerr << "Non fatal error: Line " << line.lineNumber
              << " has exceeded declared size. Expected " << dataLength
              << ", got " << line.list.size() << "\n";
  }
}

void getMotionData(const std::string& rowText, DetectionList &line) {
  std::string colText;
  GetElements col (rowText, &colText);
  col.skip(3); // we are at where the data starts

  col.skip(8); // this is where the REAL data starts
  if (colText == "4") { col.next();
    col.next(); col.next(); // skip 2
    unsigned int dataLength = std::stoi(colText); col.next();
    line.motion.reserve(dataLength);
    while (col.hasNext()) {
      double reading = fabs(std::stod(colText)); col.next();
      line.motion.push_back(reading);
    }
    if (line.motion.size() > dataLength) {
      std::cerr << "Non fatal error: Line " << line.lineNumber
                << " has exceeded declared size. Expected " << dataLength
                << ", got " << line.list.size() << "\n";
    }
  }
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

