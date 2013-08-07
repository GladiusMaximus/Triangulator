#!/bin/sh
g++ *.cpp -lm -std=c++0x -pedantic -O3 -DNDEBUG -fwhole-program -funroll-loops -o r-release.out
