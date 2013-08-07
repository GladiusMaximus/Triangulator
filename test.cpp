#include <iostream>
/******************************************************************************
  Includes
******************************************************************************/
//#define NDEBUG
#include <assert.h>
#include "test.h"
#include "geometry.h"
#include "data.h"
//#define BILATERAL

/******************************************************************************
  Constants
******************************************************************************/

const long int ITERATIONS = 1000000;
//const int ITERATIONS = 500;

/******************************************************************************
  Functions
******************************************************************************/

void test_all() {
  testPointEquals();
  testCircleEquals();
  testRectangleEquals();
  testBilateral();
  testInside();
}

void testPointEquals() {
  for (long int i = 0; i < ITERATIONS; i++) {
    Point a = randomPoint(), b = transform(a, square(1)), c = b;
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
        b = {transform(a.center, square(1)), a.radius + 1},
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
        b = transform(a, square(1), square(1)),
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
#ifdef BILATERAL
  for (int i = 0; i < ITERATIONS; i++) {
    Rectangle temp = randomRectangle();
    Point a = transform(temp.bottomleft, square(-MIN_DIMENSION)),
          b = transform(temp.topright, square(-MIN_DIMENSION)),
          target;
    target = randomPoint(temp);
    Circle t1 = {a, distance(a, target)}, t2 = {b, distance(b, target)};
    std::vector<Point> solutions = bilateral(t1, t2);
    bool success = false;
    for (std::vector<Point>::iterator it = solutions.begin();
         it != solutions.end(); ++it) {
      if (*it == target)
        success = true;
    }
    assert(success);
  }
#endif
}

void showBilateral(Circle a, Circle b) {
  std::vector<Point> solutions =
      bilateral(a, b);
  for (std::vector<Point>::iterator it = solutions.begin();
       it != solutions.end(); ++it)
  std::cout << pointToString(*it)
            << std::endl;
}

void testInside() {
  Rectangle asquare;
  asquare.bottomleft = randomPoint();
  asquare.topright = transform(asquare.bottomleft, square(2));
  Point a = transform(asquare.bottomleft, square(1)),
        b = transform(asquare.bottomleft, {9, 1}),
        c = transform(asquare.bottomleft, {-9, 1}),
        d = transform(asquare.bottomleft, {1, 9}),
        e = transform(asquare.bottomleft, {1, -9});
  assert(inside(asquare, a));
  assert(! inside(asquare, b));
  assert(! inside(asquare, c));
  assert(! inside(asquare, d));
  assert(! inside(asquare, e));

}
