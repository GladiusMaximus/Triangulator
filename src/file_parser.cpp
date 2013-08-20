#include <vector>
#include <iostream>
#include "file_parser.h"

/******************************************************************************
  CSV iterator
******************************************************************************/

#define PYTHON_READABLE
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

std::vector<std::vector<FilterReading>> parseMRMData(const std::string& fileName) {
  std::vector<std::vector<FilterReading>> data; data.reserve(DATA_POINTS);
  std::string rowText, colText;
  long double firstTime = 0.0;
  unsigned int line = 0;
  for (GetLines row (fileName, &rowText); row.hasNext(); row.next()) {
    // Setup
    ++line;
    FilterReading current; reset(current);
    std::vector<FilterReading> rowVec; rowVec.reserve(ELEMENTS);
    GetElements col (rowText, &colText);
    //col.next() is implied by the constructor

    // Begin parsing line
    if (isdigit(colText[0])) { // first element is always timestamp (if its first char a number)
      current.timestamp = std::stold(colText); col.next();
      if (firstTime == 0.0)
        firstTime = current.timestamp;
      current.timestamp = current.timestamp - firstTime;
      if (colText == "MrmDetectionListInfo") { col.next();
        current.messageID = std::stoi(colText); col.next();
        unsigned int dataLength = std::stoi(colText); col.next();
        if (dataLength == 0)
          continue;
        while (col.hasNext()) { // Then the rest of the line is data
          current.index = std::stoi(colText); col.next();
          current.magnitude = std::stof(colText) / MAX_MAGNITUDE; col.next();
          rowVec.push_back(current);
        }
        if (rowVec.size() > dataLength) {
          std::cerr << "Non fatal error: Line " << line
                    << " has exceeded declared size. Expected " << dataLength
                    << ", got " << rowVec.size() << "\n";
        }
        data.push_back(rowVec);
      }
    }
  }
  return data;
}

void humanReadable(std::vector<std::vector<FilterReading>> data) {
  for (std::vector<FilterReading> row : data) {
    std::cout << "Row: ";
    std::cout << "Time: " << row[0].timestamp << ", ID: " << row[0].messageID;
    for (FilterReading elem : row) {
      std::cout << ", index: " << elem.index << ", magnitude: " << elem.magnitude;
    }
    std::cout << "\n";
  }
}

void pythonReadable(std::vector<std::vector<FilterReading>> data) {
  std::cout << "data = [\n";
  for (std::vector<FilterReading> row : data) {
    std::cout << "    [" << row[0].timestamp << ", ";
    for (FilterReading elem : row) {
      std::cout << "(" << elem.index << ", " << elem.magnitude << "), ";
    }
    std::cout << "],\n";
  }
  std::cout << "]\n";
}

void maxVal(std::vector<std::vector<FilterReading>> data) {
  FilterReading max;
  for (std::vector<FilterReading> row : data) {
    reset(max);
    max.magnitude = -1;
    for (FilterReading elem : row) {
      if (elem.magnitude > max.magnitude)
        max =  elem;
    }
    std::cout << max.timestamp << " " << max.index << " " << max.magnitude << "\n";
  }
}

void avgVal(std::vector<std::vector<FilterReading>> data) {
  FilterReading sum;
  for (std::vector<FilterReading> row : data) {
    sum = row[0];
    for (FilterReading elem : row) {
      sum.index += elem.index * elem.magnitude;
      sum.magnitude += elem.magnitude;
    }
    std::cout << sum.timestamp << " " << sum.index / sum.magnitude << " "
              << sum.magnitude << "\n";
  }
}

std::string readingToString(const FilterReading &k) {
  std::ostringstream out;
  out << "Time: " << k.timestamp << ", ID: " << k.messageID << ", index: "
      << k.index << ", magnitude: " << k.magnitude;
  return out.str();
}

void reset(FilterReading &k) {
  k.timestamp = 0.0;
  //k.timeSince = 0.0;
  k.messageID = 0;
  //k.lastID = 0;
  k.index = 0;
  k.magnitude = 0.0;
}

void copy(FilterReading& lhs, const FilterReading& rhs) {
  lhs.timestamp = rhs.timestamp;
  //lhs.timeSince = rhs.timeSince;
  lhs.messageID = rhs.messageID;
  //lhs.lastID = rhs.lastID;
  lhs.index = rhs.index;
  lhs.magnitude = rhs.magnitude;
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

