set terminal png
set output "CO_PES.png"
set xlabel "Bond length (Angstroms)"
set ylabel "Energy (Hartree)"

plot "PES_Data.dat" u 1:2 w linespoints

