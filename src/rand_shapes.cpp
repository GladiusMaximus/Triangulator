/******************************************************************************
  Includes
******************************************************************************/
#include <stdlib.h> // simple random (rand() function)
#include "rand_shapes.h"
#include "geometry.h"

/******************************************************************************
  Functions
******************************************************************************/

Circle randomCircle() {
  return {randomPoint(), randInt(MIN_DIMENSION, MAX_POINT)};
}

Rectangle randomRectangle() {
  Point topright = randomPoint(MIN_DIMENSION + 1, MAX_POINT),
         bottomleft = randomPoint({ORIGIN, topright + (-MIN_DIMENSION)});
  return {bottomleft, topright};
}

Point randomPoint() {
  return randomPoint(0, MAX_POINT);
}

Point randomPoint(Number low, Number high) {
  return randomPoint({{low, low}, {high, high}});
}

Point randomPoint(const Rectangle &boundary) {
  return {randInt(boundary.bottomleft.x, boundary.topright.x),
          randInt(boundary.bottomleft.y, boundary.topright.y)};
}

Number randInt(Number min, Number max) {
  return Number(rand() % int(max - min)) + min;
}

Number randInt(Number min, Number max, int seed) {
  srand(seed);
  return Number(rand() % int(max - min)) + min;
}
