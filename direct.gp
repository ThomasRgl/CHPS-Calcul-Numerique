#
set datafile separator ";"


#
set grid

#
set key autotitle columnhead
set ylabel "cycles"
set xlabel "array size (Kib)" 

set logscale x 2
set logscale y 2


set xtic rotate by -45 scale 0 

############################################

img1 = "img/a.png"
title1 = "aaaaaaaaaaa"

set title title1

##
set terminal "png" size 800,400
set output img1

plot "data/DGBSV.dat" using 5:9 w lp

############################################

img1 = "img/b.png"
title1 = "aaaaaaaaaaa"

set title title1

##
set terminal "png" size 800,400
set output img1

plot "data/DGBTRF-S.dat" using 5:9 w lp

############################################

img1 = "img/c.png"
title1 = "aaaaaaaaaaa"

set title title1

##
set terminal "png" size 800,400
set output img1

plot "data/MANUEL.dat" using 5:9 w lp


