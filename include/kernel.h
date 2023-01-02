#include "atlas_headers.h"
#include "lib_poisson1D.h"


void a( double *restrict AB, double *restrict RHS, int *restrict ipiv, int NRHS, int la, int ku, int kl, int lab );
void b( double *restrict AB, double *restrict RHS, int *restrict ipiv, int NRHS, int la, int ku, int kl, int lab );
void c( double *restrict AB, double *restrict RHS, int *restrict ipiv, int NRHS, int la, int ku, int kl, int lab );

