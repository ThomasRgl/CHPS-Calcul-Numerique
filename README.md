# CHPS-Calcul-Numerique

# /!\  The file has been modified /!\

##########################################################
# README
#
# Thomas ROGLIN
##########################################################

# File Organisation

This directory contains the code corresponding to the solution
of Poisson 1D problem by direct method or iterative method.
It is organized in five directories:
src/ 
include/
bin/
img/
data/

"src" contains the source codes, "include" contains the 
header files and "bin" contains the executables. "data" contains
the all the .dat files generate by the programs and img contains
the graphs generate by the plot scripts.

src/bench_iter
src/bench_direct

this two folders contains the source code that do all the benchmarks
and generate all the data.

# HOW TO LAUNCH

The best way to launch the program is to launch the launch.sh script.
It will automaticly create all the folders needed,
compile all the program and launch all the executable.

$ ./launch.sh

You can comments some lines if you don't want to 
execute all the programs.


You can uncomment the gnuplot calls, but the script will 
crash if one of the executable was not executed.


# Makefile 

The compilation and execution can be done using the Makefile.

Here are the principal targets: 
testenv: bin/tp_testenv
run_tpPoisson1D_direct: bin/tp_poisson1D_direct
run_tpPoisson1D_iter: bin/tp_poisson1D_iter


