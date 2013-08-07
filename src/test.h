#ifndef TEST_H_
#define TEST_H_

// Includes
#include "geometry.h"

// Functions
  // Tests
    void test_all();
    void testPointEquals();
    void testCircleEquals();
    void testRectangleEquals();
    void testBilateral();
    void testInside();
  // Debugging
    void showBilateral(Circle a, Circle b);

#endif // TEST_H_
