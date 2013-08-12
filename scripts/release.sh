#!/bin/sh
# run from project root
. ./scripts/util.sh

file="./build/release"
rm -f $file

g++ $source $compile_flags $release_flags -o $file

if [ $? -eq 0 ]; then
    echo_heading "Build Done!"
    if [ $exec ]; then
        printf "Executing program\n\n\n"
        ./build/release $args
        printf "Program terminated\n\n\n"
    fi
    return 0
else
    echo_heading "Build Failed!"
    return 1
fi
