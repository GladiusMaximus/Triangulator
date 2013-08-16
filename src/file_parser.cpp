#include <iostream>
#include "file_parser.h"

/******************************************************************************
  CSV iterator
******************************************************************************/

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

void parseMRMData(const std::string& fileName) {
  FilterReading current, last; reset(current); reset(last);
  std::string rowText, colText;
  int line = 0, elem = 0;
  int tmpIndex, tmpMagnitude, dataLength = 0;
  for (GetLines row (fileName, &rowText); row.hasNext(); row.next()) {
    // Setup
    ++line;
    copy(last, current);
    reset(current);
    GetElements col (rowText, &colText);
    //col.next() is implied by the constructor

    // Begin parsing line
    if (isdigit(colText[0])) { // first element is always timestamp (if its a number)
      current.timestamp = std::stold(colText); col.next();
      if (colText == "MrmDetectionListInfo") { col.next();
        current.messageID = std::stoi(colText); col.next();
        dataLength = std::stoi(colText); col.next();
        elem = 0;
        while (col.hasNext()) { // Then the rest of the line is data
          if (elem >= dataLength) {
            std::cerr << "Too many datapoints on " << line << "\nExpecting: "
                      << dataLength << ", Got at least: " << elem << "\n";
            break;
          }
          tmpIndex = std::stoi(colText); col.next();
          tmpMagnitude = std::stoi(colText); col.next();

          sum += tmpMagnitude;
          current.index += tmpIndex * tmpMagnitude;
          ++elem;
        }
        //if (elem != dataLength * 2) std::cerr << "not enough datapoints\n";
        //std::cout << readingToString(current) << " found on line: " << line << "\n";
        std::cout << current.timestamp - 1376510285.913 << " "
                  << current.index / sum << " "
                  << sum / 1000000 << "\n";
      }
    }
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

