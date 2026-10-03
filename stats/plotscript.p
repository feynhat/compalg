set term png
set xlabel "Size of matrices"
set ylabel "Time to solve (in ms)"
set output "qqmat_solve.png"
set title "Solving rational matrices."
set xrange [-1:10]
plot "qq_data" u 1:2 w lines t ""

set term png
set xlabel "Size of matrices."
set ylabel "Time to solve (in ms)."
set output "fmat_solve.png"
set title "Solving floating-point matrices."
set xrange [-1:100]
plot "f_data" u 1:2 w lines t ""
