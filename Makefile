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
BENCH_DIRECT_DIR=$(TPDIRSRC)/bench_direct
BENCH_ITER_DIR=$(TPDIRSRC)/bench_iter

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
OBJTP2ITER= lib_poisson1D.o lib_iter_poisson1D.o tp_poisson1D_iter.o
OBJTP2DIRECT= lib_poisson1D.o tp_poisson1D_direct.o

OBJ_DIRECT_BENCH= lib_poisson1D.o kernel_direct.o tools.o bench_direct.o
OBJ_DIRECT_ERR_BENCH= lib_poisson1D.o kernel_direct.o tools.o bench_direct_err.o

OBJ_ITER_BENCH= lib_poisson1D.o lib_iter_poisson1D.o kernel_iter.o tools.o bench_iter.o
OBJ_ITER_ERR_BENCH= lib_poisson1D.o lib_iter_poisson1D.o kernel_iter.o tools.o bench_iter_err.o
OBJ_ITER_CONV_BENCH= lib_poisson1D.o lib_iter_poisson1D.o kernel_iter.o tools.o bench_iter_conv.o
OBJ_ITER_ITE_BENCH= lib_poisson1D.o lib_iter_poisson1D.o kernel_iter.o tools.o bench_iter_ite.o


# OBJ_ITER_BENCH= lib_poisson1D.o lib_iter_poisson1D.o kernel.o tools.o bench.o
# OBJ_ITER_ERR_BENCH= lib_poisson1D.o kernel.o tools.o direct_err_bench.o
#
#

# all: bin/tp_testenv bin/tpPoisson1D_iter bin/tpPoisson1D_direct
all: bin/tp_testenv bin/tpPoisson1D_direct bin/bench_direct bin/bench_direct_err bin/tpPoisson1D_iter  bin/bench_iter_conv  bin/bench_iter_err bin/bench_iter  bin/bench_iter_ite
# all:  bin/bench_iter_conv

####################################################################
#
# testenv: bin/tp_testenv
#
# tpPoisson1D_iter: bin/tpPoisson1D_iter
#
# tpPoisson1D_direct: bin/tpPoisson1D_direct
#
# bench_direct: bin/bench_direct
#
# bench_direct_err: bin/bench_direct_err
#
#####################################################################

tp_env.o: $(TPDIRSRC)/tp_env.c
	$(CC) $(OPTC) -c $(INCL) $(TPDIRSRC)/tp_env.c 

lib_poisson1D.o: $(TPDIRSRC)/lib_poisson1D.c
	$(CC) $(OPTC) -c $(INCL) $(TPDIRSRC)/lib_poisson1D.c 

lib_iter_poisson1D.o: $(TPDIRSRC)/lib_iter_poisson1D.c
	$(CC) $(OPTC) -c $(INCL) $(TPDIRSRC)/lib_iter_poisson1D.c 

tp_poisson1D_iter.o: $(TPDIRSRC)/tp_poisson1D_iter.c
	$(CC) $(OPTC) -c $(INCL) $(TPDIRSRC)/tp_poisson1D_iter.c  

tp_poisson1D_direct.o: $(TPDIRSRC)/tp_poisson1D_direct.c
	$(CC) $(OPTC) -c $(INCL) $(TPDIRSRC)/tp_poisson1D_direct.c  

tools.o: $(TPDIRSRC)/tools.c
	$(CC) $(OPTC) -c $(INCL) $(TPDIRSRC)/tools.c  


## DIRECT ## 

bench_direct.o: $(BENCH_DIRECT_DIR)/bench_direct.c
	$(CC) $(OPTC) -c $(INCL) $(BENCH_DIRECT_DIR)/bench_direct.c  

bench_direct_err.o: $(BENCH_DIRECT_DIR)/bench_direct_err.c
	$(CC) $(OPTC) -c $(INCL) $(BENCH_DIRECT_DIR)/bench_direct_err.c  

kernel_direct.o: $(BENCH_DIRECT_DIR)/kernel_direct.c
	$(CC) $(OPTC) $(OFLAGS) -c $(INCL) $(BENCH_DIRECT_DIR)/kernel_direct.c  
#
# bench_iter_err.o: $(BENCH_ITER_DIR)/bench_iter_err.c
# 	$(CC) $(OPTC) -c $(INCL) $(BENCH_ITER_DIR)/bench_direct_err.c  
#
# kernel_iter.o: $(BENCH_ITER_DIR)/kernel_iter.c
# 	$(CC) $(OPTC) $(OFLAGS) -c $(INCL) $(BENCH_ITER_DIR)/kernel_direct.c  
#


## ITER ## 

bench_iter.o: $(BENCH_ITER_DIR)/bench_iter.c
	$(CC) $(OPTC) -c $(INCL) $(BENCH_ITER_DIR)/bench_iter.c  

bench_iter_err.o: $(BENCH_ITER_DIR)/bench_iter_err.c
	$(CC) $(OPTC) -c $(INCL) $(BENCH_ITER_DIR)/bench_iter_err.c  

bench_iter_conv.o: $(BENCH_ITER_DIR)/bench_iter_conv.c
	$(CC) $(OPTC) -c $(INCL) $(BENCH_ITER_DIR)/bench_iter_conv.c  

bench_iter_ite.o: $(BENCH_ITER_DIR)/bench_iter_ite.c
	$(CC) $(OPTC) -c $(INCL) $(BENCH_ITER_DIR)/bench_iter_ite.c  



kernel_iter.o: $(BENCH_ITER_DIR)/kernel_iter.c
	$(CC) $(OPTC) $(OFLAGS) -c $(INCL) $(BENCH_ITER_DIR)/kernel_iter.c  



#####################################################################



bin/tp_testenv: $(OBJENV) 
	$(CC) -o bin/tp_testenv $(OPTC) $(OBJENV) $(LIBS)

bin/tpPoisson1D_iter: $(OBJTP2ITER)
	$(CC) -o bin/tpPoisson1D_iter $(OPTC) $(OBJTP2ITER) $(LIBS)

bin/tpPoisson1D_direct: $(OBJTP2DIRECT)
	$(CC) -o bin/tpPoisson1D_direct $(OPTC) $(OBJTP2DIRECT) $(LIBS)



bin/bench_direct: $(OBJ_DIRECT_BENCH)
	$(CC) -o bin/bench_direct $(OPTC) $(OBJ_DIRECT_BENCH) $(LIBS)

bin/bench_direct_err: $(OBJ_DIRECT_ERR_BENCH)
	$(CC) -o bin/bench_direct_err $(OPTC) $(OBJ_DIRECT_ERR_BENCH) $(LIBS)


bin/bench_iter: $(OBJ_ITER_BENCH)
	$(CC) -o bin/bench_iter $(OPTC) $(OBJ_ITER_BENCH) $(LIBS)

bin/bench_iter_err: $(OBJ_ITER_ERR_BENCH)
	$(CC) -o bin/bench_iter_err $(OPTC) $(OBJ_ITER_ERR_BENCH) $(LIBS)

bin/bench_iter_conv: $(OBJ_ITER_CONV_BENCH)
	$(CC) -o bin/bench_iter_conv $(OPTC) $(OBJ_ITER_CONV_BENCH) $(LIBS)

bin/bench_iter_ite: $(OBJ_ITER_ITE_BENCH)
	$(CC) -o bin/bench_iter_ite $(OPTC) $(OBJ_ITER_ITE_BENCH) $(LIBS)




#####################################################################


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
