#ifndef GEOMETRY_H_
#define GEOMETRY_H_

// Includes
#include <vector>
#include <string>
#include <cfloat>


// Data types and constants
  typedef long double Number;
  // Number may change to float or something else, with higher percision.
  // for today's implementation of Number,
  // this is the error margin you should use:
  const Number ERROR_MARGIN  = LDBL_EPSILON;

  typedef struct {
      Number x, y;
  } Point;

  typedef struct {
      Point center;
      Number radius;
  } Circle;

  typedef struct {
      Point bottomleft, topright;
  } Rectangle;

  Point const ORIGIN = {0, 0};

// Functions
  // Geometric functions
    Point average(std::vector<Point> list);
    Point transform(const Point &origin, const Point &direction);
    Rectangle transform(const Rectangle &origin, const Point &direction1,
                        const Point &direction2);
    Rectangle square(Number a, Number b);
    Point between(Point a, Point b);
    bool inside(const Rectangle &a, const Point &b);
  // Arithmetic functions
    Number sqr(Number a);
    Number delta(Number a, Number b);
    bool almostEqual(Number a, Number b);
  // Stringy functions
    std::string pointToString(Point const &p);
    std::string circleToString(Circle const &c);
    std::string rectangleToString(Rectangle const &r);


// Operators
  // Arithmetic Point operators
    // Euclidean distance
    Number operator-(const Point& a, const Point& b);
    // Apply a slide transformation to origin along direction
    Point operator+(const Point& origin, const Point& direction);
    // Apply a slide transformation; add direction to each coordinate of the point
    Point operator+(const Point& origin, const Number direction);
    // Scale a point; Dialation
    Point operator*(const Point& origin, const Number scale);
    // Invert a point; You can think of this as reflection across the line y = x
    Point operator-(const Point& a);
  // Point comparison operators
    // If rhs < lhs in both coordinates
    bool operator<(const Point& rhs, const Point& lhs);
    bool operator>(const Point& rhs, const Point& lhs);
    bool operator<=(const Point& rhs, const Point& lhs);
    bool operator>=(const Point& rhs, const Point& lhs);
  // Equals
    bool operator==(const Point& lhs, const Point& rhs);
    bool operator==(const Circle& lhs, const Circle& rhs);
    bool operator==(const Rectangle& lhs, const Rectangle& rhs);
  // Not equals
    bool operator!=(const Point& lhs, const Point& rhs);
    bool operator!=(const Circle& lhs, const Circle& rhs);
    bool operator!=(const Rectangle& lhs, const Rectangle& rhs);
  // Stream operators
    std::ostream& operator<<(std::ostream &strm, const Point &a);
    std::ostream& operator<<(std::ostream &strm, const Circle &a);
    std::ostream& operator<<(std::ostream &strm, const Rectangle &a);

#endif // GEOMETRY_H_
