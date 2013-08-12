#!/bin/sh

gdb=0  # drop into gdb after compiling a debug version
debug_flags="-g -O0"  # flags for debug version

exec=1  # execute program after compiling a release version
release_flags="-O3"  # flags for release version

# flags for both debug and release follow
compile_flags="-std=c++11 -pedantic -Wall -Wextra -Wshadow -Wpointer-arith -Wcast-qual"
source="./src/*.cpp"
args=""


echo_heading () {
    printf "\n\n====================%s====================\n\n" "$1"
}
