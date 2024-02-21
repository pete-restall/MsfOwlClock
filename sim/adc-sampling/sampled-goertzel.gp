set datafile separator ","
set key autotitle columnhead
#set term qt size 3840, 2160
plot for [col=2:2] "sampled-goertzel.csv" using 1:col with lines
pause -1
