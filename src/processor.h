#ifndef PROCESSOR_H_
#define PROCESSOR_H_

// Includes
#include <vector>
#include "geometry.h"

// Types

typedef struct {
  Point answer;
  Number certainty;
  std::vector<Point> allSolutions;
  std::vector<Number> deviation;
} Result;

typedef struct {
  std::vector<std::vector<Number>> data;
  std::vector<Result> results;
  std::vector<Circle> radarLocations;
  size_t radarCount;
  size_t sampleCount;
  Number sampleRate;
  Rectangle field;
} DataSuite;

// Functions
DataSuite makeDataSuite(size_t radars, size_t samples, Number sampleRate);
DataSuite makeDataSuite(Point target, std::vector<Circle> radarLocations,
                        size_t radars, Number dataRate, Number stddev,
                        long seed = 0);
std::string checkDataSuite(const DataSuite& d);
std::string printDataSuite(const DataSuite& d);
void processData(DataSuite& d); // Not const!!

#endif // DATA_H_
