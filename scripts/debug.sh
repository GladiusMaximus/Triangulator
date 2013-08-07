#!/bin/sh
# run from project root
. ./scripts/util.sh

file="./build/debug"
rm -f $file

g++ $source $compile_flags $debug_flags -o $file $parse_output

if [ $? -eq 0 ]; then
    echo_heading "Build Done!"
    if [ $gdb ]; then
        gdb $file -ex "source ./scripts/stl.gdb"
    fi
    return 0
else
    echo_heading "Build Failed!"
    return 1
fi


