
/******************************************************************************
  Run main unit test
******************************************************************************/
//#include "test.h"
//int main() {
  //testAll();
  //return 0;
//}


/******************************************************************************
  Interactively test bilateral function
******************************************************************************/
//#include <iostream>
//#include "geometry.h"
//using namespace std;
//int main() {
  //Point target = {3, 3};
  //Circle a = {{0, 0}, 4.24264},
         //b = {{6, -1}, 5};
  //cout << "Hello, World!" << endl;
  //cout << "Circle a is " << a << ", Circle b is " << b << ", target is "
       //<< target << endl;
  //cout << "The target point is " << a.center - target
       //<< " units away from the center of circle a." << endl
       //<< "The radius of a is " << a.radius
       //<< ", therefore target is a point on circle a" << endl;
  //cout << "The target point is " << b.center - target
       //<< " units away from the center of circle b." << endl
       //<< "The radius of b is " << b.radius
       //<< ", therefore target is a point on circle b" << endl;
  //cout << "The target point is at one of the intersections of << endl
       //<< [" << a << "] and, [" << b << endl
       //<< "Let us see what bilateral thinks their intersection is... " << endl
       //<< "(I am turning on bilateral debugging messages for you)" << endl;
  //bilateral(a, b, true);
  //return 0;
//}

/******************************************************************************
  Generate test data
******************************************************************************/
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
  std::cout << "Is dt data fine? " << (checkDataSuite(dt)) << std::endl;

  processData(dt);

  std::cout << printDataSuite(dt) << std::endl;

  return 0;
}
