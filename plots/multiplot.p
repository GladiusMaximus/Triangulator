# GNUPlot script!!!!

data_file2 = "waverage.data"
title_1 = "waverage"
data_file1 = "max_val.data"
title_2 = "max_val"

columns = "1:2:($3/100000)"

set macros
#set title "Bouncing ball"
set xlabel "Time from start (seconds)"
set ylabel "Distance from radar (meters)"
set autoscale
set multiplot layout 1, 2

set title title_1
plot data_file1 using @columns with circles title "", \
     data_file1 using 1:2 with linespoints title ""

set title title_2
plot data_file2 using @columns with circles title "", \
     data_file2 using 1:2 with linespoints title ""
     
unset multiplot

