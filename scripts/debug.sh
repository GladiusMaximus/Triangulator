#!/bin/sh
g++ *cpp              \
    -g                \
    -std=c++0x        \
    -pedantic         \
    -Wall             \
    -Wextra           \
    -Wshadow          \
    -Wpointer-arith   \
    -Wcast-qual       \
    -o r-debug.out && \
gdb r-debug.out -ex "source stl.gdb"

