#include <stdlib.h>
#include "data.h"
#include "geometry.h"

#define MAX_POINT 100

circle random_circle() {
	return {random_point(), rand() % MAX_POINT};
}

point random_point() {
	return {rand() % MAX_POINT, rand() % MAX_POINT};
}

rectangle random_rectangle() {
	point topright = random_point(), bottomleft = random_point();
	bottomleft.x = topright.x - bottomleft.x; // make bottomleft.x < topright.x
	bottomleft.y = topright.y - bottomleft.y; // make bottomleft.x < topright.x
	return {bottomleft, topright};
}

