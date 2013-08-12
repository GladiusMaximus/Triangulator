/******************************************************************************
  Includes
******************************************************************************/
#include <stdio.h>
#include <math.h>
#include <sstream>
#include <math.h>
#include "geometry.h"

/******************************************************************************
  Geometric funcions
******************************************************************************/

int factorial(int a) {
  int result = 1;
  for (int i = 1; i <= a; ++i) {
    result *= i;
  }
  return result;
}

Point average(std::vector<Point> list) {
  Number sumX = 0.0, sumY = 0.0;
  for (std::vector<Point>::iterator it = list.begin(); it != list.end(); ++it)
    sumX += it->x, sumY += it-> y;
  return {sumX / list.size(), sumY / list.size()};
}

Rectangle transform(const Rectangle &origin, const Point &direction1,
                    const Point &direction2) {
  return {origin.bottomleft + direction1,
          origin.topright + direction2};
}

Rectangle square(Number a, Number b) {
  return {{a, a}, {b, b}};
}

Point between(Point a, Point b) {
  return {a.x + b.x / 2, a.y + b.y / 2};
}

bool inside(const Rectangle & a, const Point & b) {
  return a.bottomleft <= b && b <= a.topright;
}

/******************************************************************************
  Arithmetic functoins
******************************************************************************/

Number sqr(Number a) {
  return a * a;
}

Number delta(Number a, Number b) {
  return fabs(a - b);
}

bool almostEqual(Number a, Number b) {
  return delta(a, b) < ERROR_MARGIN;
}

/******************************************************************************
  Stringy functions
******************************************************************************/

std::string pointToString(Point const &p) {
  std::ostringstream ss;
  ss << "(" << p.x << ", " << p.y << ")";
  return ss.str();

}

std::string circleToString(Circle const &c) {
  std::ostringstream ss;
  ss << "a circle with center: " << pointToString(c.center) << ", and radius: "
     << c.radius;
  return ss.str();
}

std::string rectangleToString(Rectangle const &r) {
  std::ostringstream ss;
  ss << "a rectangle with bottomright: " << pointToString(r.bottomleft) << ", and "
     << "topleft: " << pointToString(r.topright);
  return ss.str();
}

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
         "distance (as the crow flies): %f\n", pointToString(diff).c_str(), d);

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
             "%f for a, and %f for b\n", aratio, bratio);

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
  if (blabber) printf("Distance between Point 0 and Point 2 is: %f\n", a);

  Point p = c1.center + (diff * (a/d));
  if (blabber) printf("The relative coordinates of Point 2: %s\n",
         pointToString(p).c_str());

  Number h = sqrt(sqr(c1.radius) - sqr(a));
  if (blabber) printf("The distance from Point 2 to an intersection point: %f, calc: %f\n", h, sqr(c1.radius) - sqr(a));

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

/******************************************************************************
  Operators
******************************************************************************/

bool operator==(const Point& lhs, const Point& rhs) {
  return (almostEqual(lhs.x, rhs.x) && almostEqual(lhs.y, rhs.y));
}

bool operator==(const Circle& lhs, const Circle& rhs) {
  return (lhs.center == rhs.center && almostEqual(lhs.radius, rhs.radius));
}

bool operator==(const Rectangle& lhs, const Rectangle& rhs) {
  return (lhs.bottomleft == rhs.bottomleft && lhs.topright == rhs.topright);
}

bool operator!=(const Point& lhs, const Point& rhs) {
  return ! (lhs == rhs);
}

bool operator!=(const Circle& lhs, const Circle& rhs) {
  return ! (lhs == rhs);
}

bool operator!=(const Rectangle& lhs, const Rectangle& rhs) {
  return ! (lhs == rhs);
}

Number operator-(const Point& a, const Point& b) {
  // Euclidean distance
  return hypot(a.x - b.x, a.y - b.y);
}

Point operator+(const Point& origin, const Point& direction) {
  // Apply a slide transformation to origin along direction
  return {origin.x + direction.x, origin.y + direction.y};
}

Point operator+(const Point& origin, const Number direction) {
  // Apply a slide transformation; add direction to each coordinate of the point
  Point transform = {direction, direction};
  return origin + transform;
}

Point operator*(const Point& origin, const Number scale) {
  // Scale a point
  return {origin.x * scale, origin.y * scale};
}

Point operator-(const Point& a) {
  return {-a.x, -a.y};
}

bool operator<(const Point& rhs, const Point& lhs) {
  return rhs.x < lhs.x && rhs.y < lhs.y;
}

bool operator>(const Point& rhs, const Point& lhs) {
  return rhs.x > lhs.x && rhs.y > lhs.y;
}

bool operator<=(const Point& rhs, const Point& lhs) {
  return rhs < lhs || rhs == lhs;
}

bool operator>=(const Point& rhs, const Point& lhs) {
  return rhs > lhs || rhs == lhs;
}

std::ostream& operator<<(std::ostream &strm, const Point &a) {
  return strm << pointToString(a);
}

std::ostream& operator<<(std::ostream &strm, const Rectangle &a) {
  return strm << rectangleToString(a);
}

std::ostream& operator<<(std::ostream &strm, const Circle &a) {
  return strm << circleToString(a);
}
