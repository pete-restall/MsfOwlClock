set datafile separator whitespace

set logscale xy 10
set xlabel "Frequency (Hz)"
set ylabel "Noise"
set arrow from 60e3, graph 0 to 60e3, graph 1 nohead
set arrow from 180e3, graph 0 to 180e3, graph 1 nohead
plot "/tmp/msf-front-end-noise.txt" u 3:4 title "Input Noise (V/Hz^-1)" with lines, "/tmp/msf-front-end-noise.txt" u 5:6 title "Output Noise (V/Hz^-1)" with lines
pause -1
