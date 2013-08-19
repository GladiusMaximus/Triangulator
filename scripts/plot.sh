#!/bin/sh

printf "Data basename: "
read base_file
#base_file="waverage"
printf "Plotting mode: "
read plot_mode
#plot_mode=1

touch plots/$base_file.data
./build/release > plots/$base_file.data
printf	 "Data points: `wc -l plots/$base_file.data | grep '[0-9][0-9]' -o`0\n"

cd plots/
export BASE_FILE=$base_file
export PLOT_MODE=$plot_mode
gnuplot plot.p


