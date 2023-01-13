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
# convergence ?

set key top left 

set title title1

##
set terminal "png" size 800,400
set output img1


plot "data/RA_ERR.dat" using 1:2 w lp title "richardson alpha",\
     "data/JACOBI_ERR.dat" using 1:2 w lp t "jacobi",\
     "data/GAUSS_ERR.dat" using 1:2 w lp t "gauss seidel"


############################################

img1 = "img/iter__ITE.png"
# title1 = " erreur des méthodes itératives au cours de leur apprentissage" 
title1 = " erreur après 10 itérations"
# convergence ?

set key top left 

set title title1

set ylabel " error "
set xlabel " taille de la matrice " 


##
set terminal "png" size 800,400
set output img1


plot "data/RA_IT.dat" using 1:2 w lp title "richardson alpha",\
     "data/JACOBI_IT.dat" using 1:2 w lp t "jacobi",\
     "data/GAUSS_IT.dat" using 1:2 w lp t "gauss seidel"



############################################

img1 = "img/iter_SPEED_CONV.png"
# title1 = " erreur des méthodes itératives au cours de leur apprentissage" 
title1 = "nombre d'iteration nécessaire pour arriver à une precision de 10-3"
# convergence ?

set key top left 

set title title1

set ylabel " iteration "
set xlabel " taille de la matrice " 


##
set terminal "png" size 800,400
set output img1


plot "data/RA_SC.dat" using 1:2 w lp title "richardson alpha",\
     "data/JACOBI_SC.dat" using 1:2 w lp t "jacobi",\
     "data/GAUSS_SC.dat" using 1:2 w lp t "gauss seidel"

############################################

img1 = "img/speediter.png"
title1 = "comparaison des temps d'executions des différentes \n méthodes de de résolution de l'equation de la chaleur"

set ylabel "time (ns)"
set xlabel "taille de la matrice (la) " 


set logscale x 2
set logscale y 2


set key top left 

set title title1

##
set terminal "png" size 800,400
set output img1

plot "data/RA_TIME.dat" using 5:9 w lp title "richardson alpha",\
     "data/JACOBI_TIME.dat" using 5:9 w lp t "jacobi",\
     "data/GAUSS_TIME.dat" using 5:9 w lp t "gauss seidel"


