/******************************************************************************
  Includes
******************************************************************************/
#include <sstream>
#include <math.h>
#include "geometry.h"

/******************************************************************************
  Geometric funcions
******************************************************************************/

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
