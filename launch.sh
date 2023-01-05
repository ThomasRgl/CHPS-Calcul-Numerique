#!/bin/sh

mkdir -p img
mkdir -p data

# make mybench
make all

#make run_testenv
#make run_tpPoisson1D_direct
#make run_tpPoisson1D_iter

#bin/mybench 12 10
bin/direct_err_bench 12 10
#
# gnuplot plot.gp
gnuplot direct.gp
#
make soft_clean
