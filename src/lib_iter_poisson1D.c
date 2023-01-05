/**********************************************/
/* lib_direct_poisson1D.c                     */
/* Numerical library developed to solve 1D    */
/* Poisson problem (Heat equation)            */
/**********************************************/

#include "lib_poisson1D.h"
#include <cblas.h>
#include "types.h"

void eig_poisson1D(double *eigval, int *la) {}

double eigmax_poisson1D(int *la) { return 0; }

double eigmin_poisson1D(int *la) { return 0; }

double richardson_alpha_opt(int *la) { 
    // A DEMONTRER

    // cheat code 
    int n = 1;
    f64 h = 1.f / ( n + 1 );
    f64 lambdaMin = 4 * pow( sin( 0 * M_PI * h ), 2);
    f64 lambdaMax = 4 * pow( sin( 1 * M_PI * h ), 2);
    

    // printf("lMax %f\n", lambdaMax);
    // printf("lMin %f\n", lambdaMin);
    return 2 / (lambdaMax + lambdaMin);
}

void richardson_alpha(double *AB, double *RHS, double *X, double *alpha_rich,
                      int *lab, int *la, int *ku, int *kl, double *tol,
                      int *maxit, double *resvec, int *nbite) {}

void extract_MB_jacobi_tridiag(double *AB, double *MB, int *lab, int *la,
                               int *ku, int *kl, int *kv) {}

void extract_MB_gauss_seidel_tridiag(double *AB, double *MB, int *lab, int *la,
                                     int *ku, int *kl, int *kv) {}

void richardson_MB(double *AB, double *RHS, double *X, double *MB, int *lab,
                   int *la, int *ku, int *kl, double *tol, int *maxit,
                   double *resvec, int *nbite) {}
