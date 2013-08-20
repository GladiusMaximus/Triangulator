#ifndef FILE_PARSER_H_
#define FILE_PARSER_H_

#include <vector>
#include <string>
#include <fstream>
#include <sstream>

class GetLines {
  public:
    GetLines(const std::string& fileName, std::string* output_, char delim_ = '\n');
    void next();
    bool hasNext();
  private:
    std::string* output;
    std::ifstream file;
    char delim;
};

class GetElements {
  public:
    GetElements(const std::string& text_, std::string* output_, char delim_ = ',');
    void next();
    bool hasNext();
  private:
    std::istringstream text;
    bool last;
    std::string* output;
    char delim;
};

typedef struct {
  long double timestamp;
  //long double timeSince;
  int messageID;
  //int lastID;
  int index;
  float magnitude;
} FilterReading;


std::vector<std::vector<FilterReading>> parseMRMData(const std::string& fileName);
void humanReadable(std::vector<std::vector<FilterReading>> data);
void pythonReadable(std::vector<std::vector<FilterReading>> data);
void maxVal(std::vector<std::vector<FilterReading>> data);
void avgVal(std::vector<std::vector<FilterReading>> data);
std::string readingToString(const FilterReading &k);
void reset(FilterReading &k);
void copy(FilterReading& lhs, const FilterReading& rhs);
void trim(std::string& str);

#endif
