#######################################
# ambre.mk
# Default options for ambre computer
#######################################
CC=gcc
LIBSLOCAL=-L/usr/lib -llapacke -llapack -lcblas -lblas  -lm
INCLUDEBLASLOCAL= #-I/usr/include
OPTCLOCAL=-fPIC -march=native
