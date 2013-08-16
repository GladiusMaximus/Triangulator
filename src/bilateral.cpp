#include <stdio.h>
#include <math.h>
#include "bilateral.h"

/******************************************************************************
  The big cheese function
******************************************************************************/

std::vector<Point> bilateral(Circle const &c1, Circle const &c2,
                             bool blabber /* = false*/) {
  if (blabber) printf("Operating on %s and %s\n", circleToString(c1).c_str(),
         circleToString(c2).c_str());

  Point diff = c2.center + (-(c1.center));
  Number d = diff - ORIGIN;
  if (blabber) printf("(dx, dy): %s, "
         "distance (as the crow flies): %Le\n", pointToString(diff).c_str(), d);

  if (d < ERROR_MARGIN) {
    if (blabber) printf("near zero d\n");
    // Check for solvability.
    if (d >= (c1.radius + c2.radius)) {
      if (blabber) printf("Circles do not intersect\n");
      if (blabber) printf("Returning the halfway solution\n");
      Number aratio = c1.radius / d;
      Number bratio = c2.radius / d;

      if (blabber) printf("Ratio of (dx, dy, d) to the triangle made by the\n"
             "farthest point the circle reaches is\n"
             "%Le for a, and %Le for b\n", aratio, bratio);

      Point af = diff * aratio, bf = diff * bratio,
            avg = between(af, bf);
      if (blabber) printf("Farthest point a reaches %s\n"
             "farthest point b reaches %s\n,"
             "Average of both: %s", pointToString(af).c_str(),
             pointToString(bf).c_str(), pointToString(avg).c_str());

      printf("Returning: [%s]\n", pointToString(avg).c_str());
      std::vector<Point> fake_solutions;
      fake_solutions.push_back(avg);
      return fake_solutions;
    }
  }

  if (d < delta(c1.radius, c2.radius)) {
    if (blabber) printf("No solution, one circle is contained in the other\n");
    if (blabber) printf("Returning []\n");
    std::vector<Point> no_solution;
    return no_solution;
  }

  Number a = (sqr(c1.radius) - sqr(c2.radius) + sqr(d)) / (2.0 * d);
  if (blabber) printf("Distance between Point 0 and Point 2 is: %Le\n", a);

  Point p = c1.center + (diff * (a/d));
  if (blabber) printf("The relative coordinates of Point 2: %s\n",
         pointToString(p).c_str());

  Number h = sqrt(sqr(c1.radius) - sqr(a));
  if (blabber) printf("The distance from Point 2 to an intersection point: %Le, calc: %Le\n", h, sqr(c1.radius) - sqr(a));

  if (h < ERROR_MARGIN || isnan(h)) {
    if (blabber) printf("h is near zero, The circles intersect at only 1 point\n"
           "Only one point in the solution\n");
    if (blabber) printf("Returning [%s]\n", pointToString(p).c_str());
    std::vector<Point> solution;
    solution.push_back(p);
    return solution;
  }

  Number rx = -diff.y * (h/d), ry = diff.x * (h/d);
  if (blabber) printf("offsets of the intersection points from Point 2: %s\n",
         pointToString({rx, ry}).c_str());

  Point solution1 = p + Point({rx, ry}),
        solution2 = p + (-Point({rx, ry}));
  if (blabber) printf("Solved!\n");

  if (blabber) printf("Returning [%s, %s]\n", pointToString(solution1).c_str(),
    pointToString(solution2).c_str());
  std::vector<Point> solutions;
  solutions.push_back(solution1);
  solutions.push_back(solution2);
  return solutions;
}
