#!/bin/sh

mkdir -p img
mkdir -p data
mkdir -p bin
mkdir -p build

rm data/*.dat

# make mybench
make -B all



##########  COMMENT OR UNCOMMENT THIS PART #########

make run_testenv
make run_tpPoisson1D_direct
make run_tpPoisson1D_iter

# create benchmark data for direct methods
bin/bench_direct 12 10
bin/bench_direct_err 12 10

#create benchmark data for iterative methods
./bin/bench_iter_conv
bin/bench_iter_err 10 10
bin/bench_iter_ite 8 10
bin/bench_iter 10 10

####################################################

#
#gnuplot direct.gp
#gnuplot iter.gp


#
make soft_clean
