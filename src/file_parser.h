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
  unsigned int index;
  double magnitude;
} Detection;

typedef struct {
  long double timestamp;
  unsigned int messageID;
  std::vector<Detection> list;
  std::vector<double> rawData;
} DetectionList;

std::vector<DetectionList> parseMRMData(const std::string& fileName);
void getNextToken(std::istream stream, char delim, std::string& output);
void humanReadable(std::vector<DetectionList> data);
void pythonReadable(std::vector<DetectionList> data);
void maxVal(std::vector<DetectionList> data);
void avgVal(std::vector<DetectionList> data);
void trim(std::string& str);

#endif
