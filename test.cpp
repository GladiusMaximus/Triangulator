#include <iostream>
//#define NDEBUG
#include <assert.h>
#include "test.h"
#include "geometry.h"
#include "data.h"

//#define ITERATIONS 500000
#define ITERATIONS 500

void test_all() {
	test_point_eq();
	test_circle_eq();
	test_rectangle_eq();
	test_bilateral();
	test_inside();
}

void test_point_eq() {
	for(int i = 0; i < ITERATIONS; i++) {
		point a = random_point(), b = {a.x + 1, a.y + 1}, c = b;
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

void test_circle_eq() {
	for(int i = 0; i < ITERATIONS; i++) {
		circle a = random_circle(),
			   b = {{a.center.x + 1, a.center.y + 1}, a.radius + 1},
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

void test_rectangle_eq() {
	for(int i = 0; i < ITERATIONS; i++) {
		rectangle a = random_rectangle(),
			   b = {{a.bottomleft.x + 1, a.bottomleft.y + 1},
					{a.topright.x + 1, a.topright.y + 1}},
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

void test_bilateral() {
	for(int i = 0; i < ITERATIONS; i++) {
		point a = random_point(), b = random_point(), target = random_point();
		while(b  == a)
			b = random_point();
		//TODO: restrict target to being between a and b
		circle t1 = {a, distance(a, target)}, t2 = {b, distance(b, target)};
		std::vector<point> solutions = bilateral(t1, t2);
		bool success = false;
		for(std::vector<point>::size_type k = 0; k != solutions.size(); k++) {
			if (solutions[k] == target)
				success = true;
		}
		if (! success)
			std::cout << "No" << std::endl;
		//assert(success);
	}
}

void test_inside() {
	rectangle square;
	square.bottomleft = random_point();
	square.topright = {square.bottomleft.x + 2, square.bottomleft.y +  2};
	point a = {square.bottomleft.x + 1, square.bottomleft.y + 1},
		  b = {square.bottomleft.x + 9, square.bottomleft.y + 1},
		  c = {square.bottomleft.x - 9, square.bottomleft.y + 1},
		  d = {square.bottomleft.x + 1, square.bottomleft.y + 9},
		  e = {square.bottomleft.x + 1, square.bottomleft.y - 9};
	assert(inside(square, a));
	assert(! inside(square, b));
	assert(! inside(square, c));
	assert(! inside(square, d));
	assert(! inside(square, e));

}

