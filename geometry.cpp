#include <math.h>
#include <sstream>
#include "geometry.h"
const Number ERROR_MARGIN  = .01;

std::string pointToString(Point const &p) {
  std::ostringstream ss;
  ss << "(" << p.x << ", " << p.y << ")";
  return ss.str();

}

std::string circleToString(Circle const &c) {
  std::ostringstream ss;
  ss << "center: " << pointToString(c.center) << ", radius: " << c.radius;
  return ss.str();
}

inline bool almostEqual(Number a, Number b) {
  return delta(a, b) < ERROR_MARGIN;
}

inline Number sqr(Number a) {
  return a * a;
}

inline Number delta(Number a, Number b) {
  return fabs(a - b);
}

bool inside(const rectangle & a, const Point & b) {
  return a.bottomleft.x <= b.x && b.x < a.topright.x &&
      a.bottomleft.y <= b.y && b.y < a.topright.y;
}

inline Point between(Point a, Point b) {
  return {a.x + b.x / 2, a.y + b.y / 2};
}

Point average(std::vector<Point> list) {
  Number sumX, sumY;
  for (std::vector<Point>::iterator it = list.begin(); it != list.end(); ++it)
    sumX += it->x, sumY += it-> y;
  return {sumX / list.size(), sumY / list.size()};
}

Number distance(Point const &a,  const Point &b) {
  // d = sqrt(dx^2 + dy^2)
  return hypot(a.x - b.x, a.y - b.y);
  //return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}

bool operator==(const Point& lhs, const Point& rhs) {
  return (almostEqual(lhs.x, rhs.x) && almostEqual(lhs.y, rhs.y));
}

bool operator==(const Circle& lhs, const Circle& rhs) {
  return (lhs.center == rhs.center && almostEqual(lhs.radius, rhs.radius));
}

bool operator==(const rectangle& lhs, const rectangle& rhs) {
  return (lhs.bottomleft == rhs.bottomleft && lhs.topright == rhs.topright);
}

bool operator!=(const Point& lhs, const Point& rhs) {
  return ! (lhs == rhs);
}

bool operator!=(const Circle& lhs, const Circle& rhs) {
  return ! (lhs == rhs);
}

bool operator!=(const rectangle& lhs, const rectangle& rhs) {
  return ! (lhs == rhs);
}

std::vector<Point> bilateral(Circle const &a, Circle const &b) {
  // Credit to: http://paulbourke.net/geometry/circlesphere/
  // (scroll down to see the specific example)
  Number ah, dx, dy, d, h, rx, ry;
  Number x2, y2;

  // dx and dy are the vertical and horizontal distances between the Circle
  // centers.
  dx = b.center.x - a.center.x;
  dy = b.center.y - a.center.y;

  // Determine the straight-line distance between the centers.
  d = hypot(dx,dy); // Suggested by Keith Briggs

  if (d == 0)

    // Check for solvability.
    if (d >= (a.radius + b.radius)) {
      // halfway solution. circles do not intersect.
      // Triangle d, dy, and dx is simmilar to new triangle with this ratio
      Number aratio = a.radius / d;
      Number bratio = b.radius / d;

      // af is the farthest Point reached by Circle a toward Circle b
      // df is the farthest Point reached by Circle b toward Circle a
      Point af = {aratio * dx, aratio * dy}, bf = {bratio * dx, bratio * dy},
          avg = between(af, bf);


      //return list
      std::vector<Point> ret;
      ret.push_back(avg);
      ret.push_back(avg);
      return ret;
    }

  if (d < delta(a.radius, b.radius)) {
    // no solution. one Circle is contained in the other
    std::vector<Point> ret;
    return ret;
  }

  // 'Point 2' is the Point where the line through the Circle
  // intersection points crosses the line between the Circle
  // centers.

  // Determine the distance from Point 0 to Point 2.
  ah = (sqr(a.radius) - sqr(b.radius) + (d*d)) / (2.0 * d) ;

  // Determine the relative coordinates of Point 2.
  x2 = a.center.x + (dx * ah/d);
  y2 = a.center.y + (dy * ah/d);

  // Determine the distance from Point 2 to any intersection Point.
  h = sqrt(sqr(a.radius) - (ah*ah));

  // Now determine the offsets of the intersection points from Point 2.
  rx = -dy * (h/d);
  ry = dx * (h/d);

  // Determine the absolute intersection points.
  Point solution1 = {x2 + rx, y2 + ry},
      solution2 = {x2 - rx, y2 - ry};

  // Return list of solutions as a vector
  std::vector<Point> ret;
  ret.push_back(solution1);
  ret.push_back(solution2);
  return ret;

}


