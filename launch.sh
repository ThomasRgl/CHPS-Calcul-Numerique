#!/bin/sh

mkdir -p img
mkdir -p data
mkdir -p bin
mkdir -p build

rm data/*.dat

# make mybench
make -B all


#make run_testenv
#make run_tpPoisson1D_direct
# make run_tpPoisson1D_iter


#bin/mybench 12 10
# bin/bench_direct_err 12 10

./bin/bench_iter_conv
bin/bench_iter_err 10 10
bin/bench_iter_ite 5 10
bin/bench_iter 10 10


#
# gnuplot direct.gp
gnuplot iter.gp


#
make soft_clean
