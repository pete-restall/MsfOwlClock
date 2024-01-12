set datafile separator ","
columns(n) = real(word(strcol(1),n))

set logscale xy 10
set xlabel "Frequency (Hz)"
set ylabel "|Z| (Ohms)"
set arrow from 10e3, graph 0 to 10e3, graph 1 nohead
set arrow from 200e6, graph 0 to 200e6, graph 1 nohead
set arrow from 10e3,0.060 to 200e6,0.060 nohead
plot "/tmp/power-bypass-caps.txt" u (columns(1)):(columns(2)) with lines
pause -1
