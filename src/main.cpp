/******************************************************************************
  Test CSV Parsing
******************************************************************************/

#include <iostream>
#include <string>
#include "file_parser.h"

const std::string fileName = "./external/rlog_000.csv";

int main() {
  pythonReadable(parseMRMData(fileName));
}
// TODO: not enough data points
// TODO: fscanf instead of csv iterators
// TODO: Error handling in csv
// TODO: sequential parsing instead of pattern matching
// TODO: feature extractor

// Next: Use strictly C++89
// Next: Use more lists and less vectors
