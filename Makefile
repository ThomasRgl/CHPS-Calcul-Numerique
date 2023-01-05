##########################################
# Makefile                               #
# Makefile for the code developed in TP1 #
#                                        #
# T. Dufaud                              #
##########################################
################################
# Variables for this makefile
################################
# 
# -- option to dedicated machine
#
# Rk: You should create a file such as your-machineName.mk
# Follow the example of the machine called "ambre" in the 
# file ambre.mk
#
HOSTNAME=$(shell hostname)
include $(HOSTNAME).mk

# 
# -- Compiler Option
OPTC=${OPTCLOCAL}

#
# -- Directories
TPDIR=.
TPDIRSRC=$(TPDIR)/src

#
# -- librairies
LIBS=${LIBSLOCAL}

# -- Include directories
INCLATLAS=${INCLUDEBLASLOCAL}
INCL= -I $(TPDIR)/include $(INCLATLAS)

OFLAGS= -O2 -march=native -mtune=native

#
#################################################################
# makefile
############
#
OBJENV= tp_env.o
OBJTP2ITER= lib_poisson1D.o tp_poisson1D_iter.o
OBJTP2DIRECT= lib_poisson1D.o tp_poisson1D_direct.o
OBJ_BENCH= lib_poisson1D.o kernel.o tools.o bench.o
OBJ_DIRECT_ERR_BENCH= lib_poisson1D.o kernel.o tools.o direct_err_bench.o
#

# all: bin/tp_testenv bin/tpPoisson1D_iter bin/tpPoisson1D_direct
all: bin/tp_testenv bin/tpPoisson1D_direct bin/mybench bin/direct_err_bench

testenv: bin/tp_testenv

tpPoisson1D_iter: bin/tpPoisson1D_iter

tpPoisson1D_direct: bin/tpPoisson1D_direct

mybench: bin/mybench

direct_err_bench: bin/direct_err_bench

tp_env.o: $(TPDIRSRC)/tp_env.c
	$(CC) $(OPTC) -c $(INCL) $(TPDIRSRC)/tp_env.c 

lib_poisson1D.o: $(TPDIRSRC)/lib_poisson1D.c
	$(CC) $(OPTC) -c $(INCL) $(TPDIRSRC)/lib_poisson1D.c 

tp_poisson1D_iter.o: $(TPDIRSRC)/tp_poisson1D_iter.c
	$(CC) $(OPTC) -c $(INCL) $(TPDIRSRC)/tp_poisson1D_iter.c  

tp_poisson1D_direct.o: $(TPDIRSRC)/tp_poisson1D_direct.c
	$(CC) $(OPTC) -c $(INCL) $(TPDIRSRC)/tp_poisson1D_direct.c  

kernel.o: $(TPDIRSRC)/kernel.c
	$(CC) $(OPTC) $(OFLAGS) -c $(INCL) $(TPDIRSRC)/kernel.c  

tools.o: $(TPDIRSRC)/tools.c
	$(CC) $(OPTC) -c $(INCL) $(TPDIRSRC)/tools.c  

bench.o: $(TPDIRSRC)/bench.c
	$(CC) $(OPTC) -c $(INCL) $(TPDIRSRC)/bench.c  

direct_err_bench.o: $(TPDIRSRC)/direct_err_bench.c
	$(CC) $(OPTC) -c $(INCL) $(TPDIRSRC)/direct_err_bench.c  






bin/tp_testenv: $(OBJENV) 
	$(CC) -o bin/tp_testenv $(OPTC) $(OBJENV) $(LIBS)

bin/tpPoisson1D_iter: $(OBJTP2ITER)
	$(CC) -o bin/tpPoisson1D_iter $(OPTC) $(OBJTP2ITER) $(LIBS)

bin/tpPoisson1D_direct: $(OBJTP2DIRECT)
	$(CC) -o bin/tpPoisson1D_direct $(OPTC) $(OBJTP2DIRECT) $(LIBS)

bin/mybench: $(OBJ_BENCH)
	$(CC) -o bin/mybench $(OPTC) $(OBJ_BENCH) $(LIBS)

bin/direct_err_bench: $(OBJ_DIRECT_ERR_BENCH)
	$(CC) -o bin/direct_err_bench $(OPTC) $(OBJ_DIRECT_ERR_BENCH) $(LIBS)



run_testenv:
	bin/tp_testenv

run_tpPoisson1D_iter:
	bin/tpPoisson1D_iter

run_tpPoisson1D_direct:
	bin/tpPoisson1D_direct

soft_clean:
	rm -f *.o 

clean:
	rm -f *.o bin/* data/* img/*
