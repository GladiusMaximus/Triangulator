#!/bin/sh
# run from project root
. ./scripts/util.sh

file="./build/release"
rm -f $file

#echo "g++ $source $compile_flags $release_flags -o $file $parse_output"
g++ $source $compile_flags $release_flags -o $file $parse_output

if [ $? -eq 0 ]; then
    echo_heading "Build Done!"
    if [ $exec ]; then
        printf "Executing program\n"
        ./build/release
        printf "Program terminated\n"
    fi
    return 0
else
    echo_heading "Build Failed!"
    return 1
fi
