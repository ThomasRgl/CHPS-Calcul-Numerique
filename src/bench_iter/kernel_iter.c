#include "atlas_headers.h"
#include "lib_poisson1D.h"

#include "kernel.h"

void alphaR( double *restrict AB, double *restrict RHS,
            int *restrict ipiv, int NRHS, int la, int ku,
            int kl, int lab, int maxit, double * resvec, 
            double * TMP, int * nbite, double * SOL,
            double * MB, double tol, double * LU ){
    
    double opt_alpha = richardson_alpha_opt(&la) ;
    richardson_alpha(AB, RHS, SOL, &opt_alpha, &lab, &la, &ku, &kl, &tol,
                     &maxit, resvec, nbite, TMP );


}


void jacobi( double *restrict AB, double *restrict RHS,
            int *restrict ipiv, int NRHS, int la, int ku,
            int kl, int lab, int maxit, double * resvec, 
            double * TMP, int * nbite, double * SOL,
            double * MB, double tol, double * LU ){
    int kv = 0;
    extract_MB_jacobi_tridiag(AB, MB, &lab, &la, &ku, &kl, &kv);
    richardson_MB(AB, RHS, SOL, MB, &lab, &la, &ku, &kl, &tol, &maxit,
    resvec, nbite, ipiv, LU, TMP);

}

void gauss( double *restrict AB, double *restrict RHS,
            int *restrict ipiv, int NRHS, int la, int ku,
            int kl, int lab, int maxit, double * resvec, 
            double * TMP, int * nbite, double * SOL,
            double * MB, double tol, double * LU ){

    int kv = 0;
    extract_MB_gauss_seidel_tridiag(AB, MB, &lab, &la, &ku, &kl, &kv);
    richardson_MB(AB, RHS, SOL, MB, &lab, &la, &ku, &kl, &tol, &maxit,
    resvec, nbite, ipiv, LU, TMP);



}
