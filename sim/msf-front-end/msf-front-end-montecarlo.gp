set datafile separator whitespace

set logscale x 10
set xlabel "Frequency (Hz)"
set ylabel "Differential ADC Input (dB)"
set arrow from 60e3, graph 0 to 60e3, graph 1 nohead
set arrow from 180e3, graph 0 to 180e3, graph 1 nohead
plot for [i=1:2:2] "/tmp/msf-front-end-montecarlo.txt" u (column(i)):(column(i + 1)) title "Run ".((i >> 1) + 1) with lines
pause -1
