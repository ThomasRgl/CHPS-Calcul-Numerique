#
set datafile separator ";"


#
set grid

#
set key autotitle columnhead
set ylabel "time (ns)"
set xlabel "taille de la matrice (la) " 

set logscale x 2
set logscale y 2


set xtic rotate by -45 scale 0 

############################################

img1 = "img/speedpoisson.png"
title1 = "comparaison des temps d'executions des différentes \n méthodes de de résolution de l'equation de la chaleur"

set key top left 

set title title1

##
set terminal "png" size 800,400
set output img1


plot "data/DGBSV.dat" using 5:9 w lp title "dgbsv", \
     "data/DGBTRF-S.dat" using 5:9 w lp t "dgbtrf + dgbtrs",\
     "data/MANUEL.dat" using 5:9 w lp t "dtbrftridiag + dgbtrs"

############################################

img1 = "img/errav_poisson_direct.png"
title1 = "erreur avant des différentes \n méthodes de de résolution de l'equation de la chaleur"

set title title1
set key top right

##
set terminal "png" size 800,400
set output img1

unset logscale y

set ylabel "erreur"



plot "data/ERR_DGBSV.dat" using 5:8 w lp title "dgbsv", \
     "data/ERR_DGBTRF-S.dat" using 5:8 w lp t "dgbtrf + dgbtrs",\
     "data/ERR_MANUEL.dat" using 5:8 w lp t "dtbrftridiag + dgbtrs"



############################################

img1 = "img/errar_poisson_direct.png"
title1 = "erreur arriere des différentes \n méthodes de de résolution de l'equation de la chaleur"

set title title1

##
set terminal "png" size 800,400
set output img1

unset logscale y


plot "data/ERR_DGBSV.dat" using 5:9 w lp title "dgbsv", \
     "data/ERR_DGBTRF-S.dat" using 5:9 w lp t "dgbtrf + dgbtrs",\
     "data/ERR_MANUEL.dat" using 5:9 w lp t "dtbrftridiag + dgbtrs"



