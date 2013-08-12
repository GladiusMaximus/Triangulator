#ifndef DATA_H_
#define DATA_H_

// Includes
#include "geometry.h"

// Functions
Circle randomCircle();
Rectangle randomRectangle();
Point randomPoint();
Point randomPoint(Number low, Number high);
Point randomPoint(const Rectangle &boundary);
Number randInt(Number min, Number max);
Number randInt(Number min, Number max, int seed);

// Constants
const int MAX_POINT = 100; // largest value for any point or radius
const int MIN_DIMENSION = 5; // smallest length for any dimension

#endif // DATA_H_
