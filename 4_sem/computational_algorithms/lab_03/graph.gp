splot 'out_newton.txt' using 1:2:3:4 with points  pointtype 7 pointsize 3 palette
show plot
pause -1

splot 'out_spline.txt' using 1:2:3:4 with points palette pointsize 3 pointtype 7
show plot
pause -1

splot 'out_newton_spline.txt' using 1:2:3:4 with points palette pointsize 3 pointtype 7
show plot
pause -1