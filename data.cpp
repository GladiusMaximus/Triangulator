/******************************************************************************
  Includes
******************************************************************************/
#include <stdlib.h>
//#include <random>
#include "data.h"
#include "geometry.h"

/******************************************************************************
  Functions
******************************************************************************/

Circle randomCircle() {
  return {randomPoint(), randInt(MIN_DIMENSION, MAX_POINT)};
}

Rectangle randomRectangle() {
  Point topright = randomPoint(MIN_DIMENSION + 1, MAX_POINT),
      bottomleft = randomPoint({square(0),
                                transform(topright, square(-MIN_DIMENSION))});
  return {bottomleft, topright};
}

Point randomPoint() {
  return randomPoint(0, MAX_POINT);
}

Point randomPoint(Number low, Number high) {
  return randomPoint(square(low, high));
}

Point randomPoint(const Rectangle &boundary) {
  return {randInt(boundary.bottomleft.x, boundary.topright.x),
          randInt(boundary.bottomleft.y, boundary.topright.y)};
}

//Number randInt(Number min, Number max) {
//  static std::default_random_engine generator;
//  std::uniform_int_distribution<int> distribution (int(min), int(max));
//  return Number(generator(distribution)) + min;
//}

Number randInt(Number min, Number max) {
  return Number(rand() % int(max - min)) + min;
}
