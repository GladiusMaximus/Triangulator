#include <stdlib.h>
#include "data.h"
#include "geometry.h"

const int MAX_POINT = 100;

Circle random_circle() {
  return {random_point(), rand() % MAX_POINT};
}

Point random_point() {
  return {rand() % MAX_POINT, rand() % MAX_POINT};
}

rectangle random_rectangle() {
  Point topright = random_point(), bottomleft = random_point();
  bottomleft.x = topright.x - bottomleft.x; // make bottomleft.x < topright.x
  bottomleft.y = topright.y - bottomleft.y; // make bottomleft.x < topright.x
  return {bottomleft, topright};
}

