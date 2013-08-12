#!/bin/sh
# drop into gdb after compiling a debug version
gdb_exec=0
# flags for debug version
debug_flags="-g -O0"

# execute program after compiling a release version
release_exec=1
# flags for release version
#release_flags="-O3 -DNDEBUG" # Don't do this, because when the assert statements
                              # go away, you get unused variable warnings
release_flags="-O3"

# flags for both debug and release follow
compile_flags="-std=c++11 -pedantic -Wall -Wextra -Wshadow -Wpointer-arith -Wcast-qual"
source="./src/*.cpp"
args=""


echo_heading () {
    printf "\n\n====================%s====================\n\n" "$1"
}
