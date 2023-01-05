#!/bin/sh

mkdir -p img
mkdir -p data

rm data/*.dat

# make mybench
make -B all


#make run_testenv
#make run_tpPoisson1D_direct
make run_tpPoisson1D_iter


#bin/mybench 12 10
#bin/direct_err_bench 12 10


#
# gnuplot direct.gp
# gnuplot iter.gp


#
make soft_clean
