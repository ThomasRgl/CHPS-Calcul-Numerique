#include "atlas_headers.h"
#include "lib_poisson1D.h"

#include "kernel.h"

void a( double *restrict AB, double *restrict RHS, int *restrict ipiv, int NRHS, int la, int ku, int kl, int lab ){
    int info; 
    
    //factoriation
    dgbtrf_(&la, &la, &kl, &ku, AB, &lab, ipiv, &info);

    //Solve
    dgbtrs_("N", &la, &kl, &ku, &NRHS, AB, &lab, ipiv, RHS, &la, &info
    #ifdef LAPACK_FORTRAN_STRLEN_END
        ,0
    #endif
    );

}


void b( double *restrict AB, double *restrict RHS, int *restrict ipiv, int NRHS, int la, int ku, int kl, int lab ){
    int info; 
    
    //factoriation
    int ierr = dgbtrftridiag(&la, &la, &kl, &ku, AB, &lab, ipiv, &info);

    //Solve
    dgbtrs_("N", &la, &kl, &ku, &NRHS, AB, &lab, ipiv, RHS, &la, &ierr
    #ifdef LAPACK_FORTRAN_STRLEN_END
        ,0
    #endif
    );

}


void c( double *restrict AB, double *restrict RHS, int *restrict ipiv, int NRHS, int la, int ku, int kl, int lab ){
    int info; 
    dgbsv_(&la, &ku, &kl, &NRHS, AB, &lab, ipiv, RHS, &la, &info);
   

}
