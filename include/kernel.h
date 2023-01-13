#include "atlas_headers.h"
#include "lib_poisson1D.h"


void a( double *restrict AB, double *restrict RHS, int *restrict ipiv, int NRHS, int la, int ku, int kl, int lab );
void b( double *restrict AB, double *restrict RHS, int *restrict ipiv, int NRHS, int la, int ku, int kl, int lab );
void c( double *restrict AB, double *restrict RHS, int *restrict ipiv, int NRHS, int la, int ku, int kl, int lab );

void alphaR( double *restrict AB, double *restrict RHS,
            int *restrict ipiv, int NRHS, int la, int ku,
            int kl, int lab, int maxit, double * resvec, 
            double * TMP, int * nbite, double * SOL,
            double * MB, double tol, double * LU );

void jacobi( double *restrict AB, double *restrict RHS,
            int *restrict ipiv, int NRHS, int la, int ku,
            int kl, int lab, int maxit, double * resvec, 
            double * TMP, int * nbite, double * SOL,
            double * MB, double tol, double * LU );

void gauss( double *restrict AB, double *restrict RHS,
            int *restrict ipiv, int NRHS, int la, int ku,
            int kl, int lab, int maxit, double * resvec, 
            double * TMP, int * nbite, double * SOL,
            double * MB, double tol, double * LU );
