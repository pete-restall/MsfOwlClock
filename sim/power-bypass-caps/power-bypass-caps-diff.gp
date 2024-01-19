set datafile separator ","
columns(n) = real(word(strcol(1),n))

fileA = "10x10uF-0805-40x4_7uF-0402-3_3V.txt"
fileB = "2x22uF-0805-60x4_7uF-0402-3_3V.txt"
fileC = "20x22uF-0805-3_3V.txt"

set logscale xy 10
set xlabel "Frequency (Hz)"
set ylabel "|Z| (Ohms)"
set arrow from 10e3, graph 0 to 10e3, graph 1 nohead
set arrow from 200e6, graph 0 to 200e6, graph 1 nohead
set arrow from 10e3,0.060 to 200e6,0.060 nohead
plot fileA u (columns(1)):(columns(2)) with lines, fileB u (columns(1)):(columns(2)) with lines, fileC u (columns(1)):(columns(2)) with lines

pause -1
