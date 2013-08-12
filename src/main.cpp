#define MAIN_3

/******************************************************************************
  Run main unit test
******************************************************************************/
#ifdef MAIN_1

#include "test.h"
int main() {
  testAll();
  return 0;
}

#endif // MAIN_1


/******************************************************************************
  Interactively test bilateral function
******************************************************************************/
#ifdef MAIN_2

#include <iostream>
#include "geometry.h"
#include "bilateral.h"
using namespace std;
int main() {
  Point target = {3, 3};
  Circle a = {{0, 0}, 4.24264},
         b = {{6, -1}, 5};
  cout << "Hello, World!\n";
  cout << "Circle a is " << a << ", Circle b is " << b << ", target is "
       << target << "\n";
  cout << "The target point is " << a.center - target
       << " units away from the center of circle a.\n"
       << "The radius of a is " << a.radius
       << ", therefore target is a point on circle a\n"
  cout << "The target point is " << b.center - target
       << " units away from the center of circle b.\n"
       << "The radius of b is " << b.radius
       << ", therefore target is a point on circle b\n";
  cout << "The target point is at one of the intersections of\n"
       << "[" << a << "] and, [" << b << "]\n";
       << "Let us see what bilateral thinks their intersection is...\n";
       << "(I am turning on bilateral debugging messages for you)\n";
  bilateral(a, b, true);
  return 0;
}

#endif // MAIN_2

/******************************************************************************
  Generate test data, and run algorithm on it
******************************************************************************/
#ifdef MAIN_3

#include <iostream>
#include <vector>
#include "geometry.h"
#include "processor.h"
using namespace std;

int main() {
  const Number STDDEV = 1.0;
  const size_t ITERATIONS = 4;
  const Number SAMPLERATE = 0.1;
  const Point TARGET = {13, 26};
  const std::vector<Circle> RADARLOCATIONS = {{{0, 0},0},
                                              {{60, 0}, 0},
                                              {{0, 60}, 0},
                                              {{60, 60}, 0}
  };

  DataSuite dt = makeDataSuite(TARGET, RADARLOCATIONS, ITERATIONS, SAMPLERATE, STDDEV);
  std::cout << "Is dt data fine? " << (checkDataSuite(dt)) << "\n";

  processData(dt);

  std::cout << printDataSuite(dt) << "\n";

  return 0;
}

#endif // MAIN_3
