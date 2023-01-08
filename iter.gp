#
set datafile separator ";"


#
set grid

#
set key autotitle columnhead
#set ylabel "time (ns)"
#set xlabel "taille de la matrice (la) " 

set ylabel "error"
set xlabel "it" 


set logscale x 2
#set logscale y 2


set xtic rotate by -45 scale 0 

############################################

img1 = "img/iter_ERR.png"
title1 = " erreur des méthodes itératives au cours de leur apprentissage"

set key top left 

set title title1

##
set terminal "png" size 800,400
set output img1


plot "data/RA_RES.dat" using 1:2 w lp title "richardson alpha",\
     "data/JACOBI_ERR.dat" using 1:2 w lp t "jacobi",\
     "data/GAUSS_ERR.dat" using 1:2 w lp t "gauss seidel"


