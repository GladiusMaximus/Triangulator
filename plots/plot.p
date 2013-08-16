# GNUPlot script!!!!

data_file = "waverage.data"

columns = "1:2:($3/100000)"

set macros
set title "Bouncing ball"
set xlabel "Time from start (seconds)"
set ylabel "Distance from radar (meters)"
set autoscale

plot data_file using @columns with circles title "", \
     data_file using 1:2 with linespoints title ""

