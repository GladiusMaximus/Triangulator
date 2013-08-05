#ifndef GEOMETRY_H_
#define GEOMETRY_H_

// Includes
#include <vector>
#include <string>

// Data types
typedef double Number;
// Number may change to float or something else.

typedef struct {
    Number x, y;
} Point;

typedef struct {
    Point center;
    Number radius;
} Circle;

typedef struct {
    Point bottomleft, topright;
} rectangle;

// Methods
Number distance(const Point &a, const Point &b);
bool inside(const rectangle &a, const Point &b);
std::vector<Point> bilateral(Circle const &a, Circle const &b);
std::string pointToString(Point const &p);
std::string circleToString(Circle const &c);
Point average(std::vector<Point> list);

// Inlines
inline Number sqr(Number a);
inline Number delta(Number a, Number b);
inline bool almostEqual(Number a, Number b);
inline Point between(Point a, Point b);

// Operators
bool operator==(const Point& lhs, const Point& rhs);
bool operator==(const Circle& lhs, const Circle& rhs);
bool operator==(const rectangle& lhs, const rectangle& rhs);
bool operator!=(const Point& lhs, const Point& rhs);
bool operator!=(const Circle& lhs, const Circle& rhs);
bool operator!=(const rectangle& lhs, const rectangle& rhs);

#endif // GEOMETRY_H_
