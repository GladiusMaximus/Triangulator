#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <functional>
#include "processor.h"

DataSuite makeDataSuite(size_t radars, size_t sampleCount, Number sampleRate) {
  std::vector<std::vector<Number>> data (sampleCount,
    std::vector<Number>(radars));
  std::vector<Result> results (sampleCount);
  std::vector<Circle> radarLocations (radars);
  return {data, results, radarLocations, radars, sampleCount, sampleRate, Rectangle()};
}

DataSuite makeDataSuite(Point target, std::vector<Circle> radarLocations, size_t sampleCount,
                        Number sampleRate, Number stddev, long seed) {
  // Make data suite
  DataSuite d = makeDataSuite(radarLocations.size(), sampleCount, sampleRate);
  d.radarLocations = radarLocations;
  d.field = {radarLocations[0].center,
             radarLocations[radarLocations.size() - 1].center};

  // Make randomness
  std::default_random_engine randomness;
  if (seed) { // If you give me a seed, use that
    randomness = std::default_random_engine(seed);
  } else { // otherwise, use the system's seed
    randomness = std::default_random_engine();
  }
  std::normal_distribution<Number> distribution (0.0, stddev);
  auto generateError = std::bind(distribution, randomness);

  // Put measurements in data suite using randomness
  for (size_t set = 0; set < d.sampleCount; ++set) {
    for(size_t radar = 0; radar < d.radarCount; ++radar) {
      Number realDistance = d.radarLocations[radar].center - target;
      Number perturbedDistance = realDistance + generateError();
      d.data[set][radar] = perturbedDistance;
    }
  }
  return d;
}

std::string checkDataSuite(const DataSuite& d) {
  if (d.data.size() != d.sampleCount)
    return "d.data.size() != d.sampleCount";
  if (d.results.size() != d.sampleCount)
    return "postProcessing && d.results.size() != d.sampleCount";
  if (d.radarLocations.size() != d.radarCount)
    return "d.radarLocations.size() != d.radarCount";
  if ((d.field.bottomleft != d.radarLocations[0].center) &&
     (d.field.topright != d.radarLocations[d.radarCount - 1].center))
    return "Incorrect bounding box";
  return "Fine!";
}

std::string printDataSuite(const DataSuite& d) {
  std::ostringstream out;

  out << d.sampleCount << " samples taken at " << d.sampleRate << " per second"
      << "by " << d.radarCount << " radars, bounded by " << d.field
      << std::endl;
  for (size_t radar = 0; radar < d.radarCount; ++radar)
    out << "Radar at: " << d.radarLocations[radar].center << std::endl;
  for (size_t set = 0; set < d.sampleCount; ++set)
    for (size_t radar = 0; radar < d.radarCount; ++radar)
      out << "Target is " << d.data[set][radar] << " units away from radar at "
          << d.radarLocations[radar].center << ", putting it at "
          << d.results[set].answer << " with " << d.results[set].certainty
          << " certainty." << std::endl;
  return out.str();
}

void processData(DataSuite& d) {
  Circle * originRadar;
  Circle * otherRadar;
  Result * result;
  std::vector<Point> possibilites;
  for (size_t set = 0; set < d.sampleCount; ++set) {
    result = &d.results[set];
    for (size_t radar = 0; radar < d.radarCount; ++radar) {
      originRadar = &d.radarLocations[radar];
      originRadar->radius = d.data[set][radar];
      //std::cout << "Origin: " << *originRadar << std::endl;
      for (size_t neighbor = 0; neighbor < d.radarCount; ++neighbor) {
        otherRadar = &d.radarLocations[neighbor];
        otherRadar->radius = d.data[set][neighbor];
        if (*originRadar == *otherRadar)
          continue; // must be two unique circles for bilateral to work
        if (otherRadar->center.x != originRadar->center.x &&
            otherRadar->center.y != originRadar->center.y)
          continue; // must not be diagonal (have at least x or y coordinate in common)
        //std::cout << "Other: " << *otherRadar << std::endl;
        possibilites = bilateral(*originRadar, *otherRadar);
        // using int not size_t on purpose, so that if solution == 0, then
        // --solution will yield a negative number terminating the loop,
        // rather than an overflow
        for (int solution = possibilites.size() - 1; solution >= 0;
          --solution) {
          //std::cout << "Possible solution: " << possibilites[solution] << std::endl;
          if (! inside(d.field, possibilites[solution]))
            possibilites.erase(possibilites.begin() + solution);
        }
        if (possibilites.size() == 1) {
          //std::cout << "Found solution: " << possibilites[0] << std::endl;
          result->allSolutions.push_back(possibilites[0]);
        } else {
          if (possibilites.size() == 0) {
            std::cout << "Non-fatal error -- No solution for: " << set
                      << " from radar at " << originRadar->center << " to radar at "
                      << otherRadar->center << std::endl;
          } else {
            std::cout << "Non-fatal error -- More than one solution for: " << set
                      << " from radar at " << originRadar->center << " to radar at "
                      << otherRadar->center << std::endl;
          }
        }
      }
    }
    result->answer = average(result->allSolutions);
    //std::cout << "Answer: " << d.results[set].answer << std::endl;
  }
}
