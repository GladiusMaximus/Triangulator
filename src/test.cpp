/******************************************************************************
  Includes
******************************************************************************/
#include <assert.h>
#include <iostream>
#include "processor.h"
#include "test.h"
#include "rand_shapes.h"
#include "bilateral.h"
#include "geometry.h"

/******************************************************************************
  Constants
******************************************************************************/

const long int ITERATIONS = 1000000;
//const int ITERATIONS = 500;

/******************************************************************************
  Functions
******************************************************************************/

void testAll() {
  testPointEquals();
  testCircleEquals();
  testRectangleEquals();
  testBilateral();
  testInside();
  testDataSuite();
}

void testPointEquals() {
  for (long int i = 0; i < ITERATIONS; i++) {
    Point a = randomPoint(), b = a + (-1), c = b;
    assert(a != b);
    assert(c == b);
    assert(c != a);
    b.x = a.x;
    assert(a != b);
    assert(c != b);
    assert(c != a);
    b.y = a.y;
    assert(b == a);
    assert(c != b);
    assert(c != a);
  }
}

void testCircleEquals() {
  for (int i = 0; i < ITERATIONS; i++) {
    Circle a = randomCircle(),
        b = {a.center + 1, a.radius + 1},
        c = b;
    assert(a != b);
    assert(c == b);
    assert(c != a);
    b.center = a.center;
    assert(a != b);
    assert(c != b);
    assert(c != a);
    b.radius = a.radius;
    assert(b == a);
    assert(c != b);
    assert(c != a);
  }
}

void testRectangleEquals() {
  for (int i = 0; i < ITERATIONS; i++) {
    Rectangle a = randomRectangle(),
              b = {a.bottomleft + 1, a.topright + 1},
              c = b;
    assert(a != b);
    assert(c == b);
    assert(c != a);
    b.bottomleft = a.bottomleft;
    assert(a != b);
    assert(c != b);
    assert(c != a);
    b.topright = a.topright;
    assert(b == a);
    assert(c != b);
    assert(c != a);
  }
}

void testBilateral() {
  for (int i = 0; i < ITERATIONS; i++) {
    Rectangle temp = randomRectangle();
    Point a = temp.bottomleft + (-MIN_DIMENSION),
          b = temp.topright + MIN_DIMENSION,
          target;
    target = randomPoint(temp);
    Circle t1 = {a, a - target}, t2 = {b, b - target};
    std::vector<Point> solutions = bilateral(t1, t2);
    bool success = false;
    for (std::vector<Point>::iterator it = solutions.begin();
         it != solutions.end(); ++it) {
      if (*it == target)
        success = true;
    }
    if (! success) { // Debug on failure
      std::cout << "Error: " << i << "th iteration failed!!" << "\n";
      std::cout << "Bounding box: " << temp << std::endl;
      std::cout << "Target: " << target << ", t1: " << t1 << ", t2: " << t2
                << std::endl;
      bilateral(t1, t2, true);  // prints out stuff
      break;
    }
  }
}

void testInside() {
  Rectangle asquare;
  asquare.bottomleft = randomPoint();
  asquare.topright = asquare.bottomleft + Point({2, 2});
  Point a = asquare.bottomleft + Point({1, 1}),
        b = asquare.bottomleft + Point({9, 1}),
        c = asquare.bottomleft + Point({-9, 1}),
        d = asquare.bottomleft + Point({1, 9}),
        e = asquare.bottomleft + Point({1, -9});
  assert(inside(asquare, a));
  assert(! inside(asquare, b));
  assert(! inside(asquare, c));
  assert(! inside(asquare, d));
  assert(! inside(asquare, e));

}

void testDataSuite() {
  const Number STDDEV = 1.0;
  const size_t REPEATS = 4;
  const Number SAMPLERATE = 0.1;
  const Point TARGET = {13, 26};
  const std::vector<Circle> RADARLOCATIONS = {{{0, 0},0},
                                              {{60, 0}, 0},
                                              {{0, 60}, 0},
                                              {{60, 60}, 0}
  };
  DataSuite dt = makeDataSuite(TARGET, RADARLOCATIONS, REPEATS, SAMPLERATE, STDDEV);
  std::cout << "Is dt data fine? " << (checkDataSuite(dt)) << "\n";

  processData(dt);
  // TODO: examine contents of processData
  // Use the same set of data each time
}
