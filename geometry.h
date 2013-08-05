#ifndef GEOMETRY_H
#define GEOMETRY_H

// Includes
#include <vector>
#include <string>

// Data types
typedef double number;
// number may change to float or something else.

typedef struct {
	number x, y;
} point;

typedef struct {
	point center;
	number radius;
} circle;

typedef struct {
	point bottomleft, topright;
} rectangle;

// Methods
number distance(const point &a, const point &b);
bool inside(const rectangle &a, const point &b);
std::vector<point> bilateral(circle const &a, circle const &b);
std::string pointToString(point const &p);
std::string circleToString(circle const &c);
point average(std::vector<point> list);

// Inlines
inline number sqr(number a);
inline number delta(number a, number b);
inline bool almostEqual(number a, number b);
inline point between(point a, point b);

// Operators
bool operator==(const point& lhs, const point& rhs);
bool operator==(const circle& lhs, const circle& rhs);
bool operator==(const rectangle& lhs, const rectangle& rhs);
bool operator!=(const point& lhs, const point& rhs);
bool operator!=(const circle& lhs, const circle& rhs);
bool operator!=(const rectangle& lhs, const rectangle& rhs);

#endif // GEOMETRY_H
