#ifndef GEOMETRY_H_
#define GEOMETRY_H_

// Includes
#include <vector>
#include <string>

// Data types
  typedef double Number;
  // Number may change to float or something else, with higher percision.
  // for today's implementation of Number,
  // this is the error margin you should use:
  const Number ERROR_MARGIN  = .001;

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

// Functions
  // Geometric functions
    Number distance(const Point &a, const Point &b);
    Point average(std::vector<Point> list);
    Point transform(const Point &origin, const Point &direction);
    Rectangle transform(const Rectangle &origin, const Point &direction1,
                        const Point &direction2);
    Rectangle square(Number a, Number b);
    Point square(Number a);
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
  // The big cheese function
    std::vector<Point> bilateral(Circle const &a, Circle const &b);

// Inlines

// Operators
  // Equals
    bool operator==(const Point& lhs, const Point& rhs);
    bool operator==(const Circle& lhs, const Circle& rhs);
    bool operator==(const Rectangle& lhs, const Rectangle& rhs);
  // Not equals
    bool operator!=(const Point& lhs, const Point& rhs);
    bool operator!=(const Circle& lhs, const Circle& rhs);
    bool operator!=(const Rectangle& lhs, const Rectangle& rhs);

#endif // GEOMETRY_H_
