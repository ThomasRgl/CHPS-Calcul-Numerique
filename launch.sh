#!/bin/sh

mkdir -p img
mkdir -p data

make all

#make run_testenv
make run_tpPoisson1D_direct
#make run_tpPoisson1D_iter

#gnuplot direct.plot
#gnuplot iter.plot

make soft_clean
