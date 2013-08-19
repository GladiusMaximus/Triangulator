# GNUPlot script!!!!

base_file = system("echo $BASE_FILE")
plot_mode = system("echo $PLOT_MODE")

print "Reading: " . base_file
set autoscale

if (plot_mode == "1") {
    print "Mode 1: circles and lines"
	set title "Bouncing ball"
	set xlabel "Time from start (seconds)"
	set ylabel "Distance from radar (meters)"
	plot (base_file . ".data") using 1:2:3 with circles notitle, \
		 (base_file . ".data") using 1:2 with linespoints notitle
}
if (plot_mode == "2") {
    print "Mode 2: bar graph"
	set title "Bouncing ball"
	set xlabel "Sum of magnitudes"
	set ylabel "Distance from radar (meters)"
	plot (base_file . ".data") with boxes notitle
}

pause -1 "Press enter to continue"

set terminal png
set output base_file . ".png"

replot

