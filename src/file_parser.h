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
    void skip(unsigned int howMany);
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
  unsigned int lineNumber;
  std::vector<Detection> list;
  std::vector<double> motion;
} DetectionList;

std::vector<DetectionList> parseMRMData(const std::string& fileName);
void getMetaData(const std::string& rowText, DetectionList &line);
void getDetectionList(const std::string& rowText, DetectionList &line);
void getMotionData(const std::string& rowText, DetectionList &line);
void humanReadable(std::vector<DetectionList> data);
void pythonReadable(std::vector<DetectionList> data);
void maxVal(std::vector<DetectionList> data);
void avgVal(std::vector<DetectionList> data);
void trim(std::string& str);

#endif
