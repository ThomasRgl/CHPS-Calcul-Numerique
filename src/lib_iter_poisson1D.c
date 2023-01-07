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
    // graphe avec diff alpha

    // cheat code 
    int n = 1;
    f64 h = 1.f / ( n + 1 );
    f64 lambdaMin = 4 * pow( sin( 0 * M_PI * h ), 2);
    f64 lambdaMax = 4 * pow( sin( 1 * M_PI * h ), 2);
    

    // printf("lMax %f\n", lambdaMax);
    // printf("lMin %f\n", lambdaMin);
    return 2 / (lambdaMax + lambdaMin);
}

void richardson_alpha(double *AA, double *RHS, double *X, double *alpha_rich,
                      int *lab, int *la, int *ku, int *kl, double *tol,
                      int *maxit, double *resvec, int *nbite) {

    double * TMP = (double *)calloc(*la, sizeof(double));

    int it = 0;
    printf("alpha : %lf\n", *alpha_rich);

    // norm(b - A*x)/norm(b);
    // TMP = b - Ax
    float norm_b = cblas_dnrm2(*la, RHS, 1 );
    float norm_bmAx = 0;

    // TMP =  AA * X
    // TMP = Ax
    cblas_dgbmv( CblasColMajor, CblasNoTrans, *la, *la, *kl, *ku, 1, AA, *lab, X, 1, 0, TMP, 1);
    // TMP = TMP +  -RHS
    // TMP = Ax - B
    cblas_daxpy(*la, -1, RHS, 1, TMP, 1);
    norm_bmAx = cblas_dnrm2(*la, TMP, 1 );
    resvec[it] = norm_bmAx/norm_b;

    while( pow(resvec[it],2) > pow(*tol,2) && it < *maxit ){
        it ++;
    
        // x = x - alpha * TMP
        // x = x - alpha * ( Ax - b)
        cblas_daxpy(*la, *alpha_rich * (-1), TMP, 1, X, 1);
 
        // TMP =  AA * X
        // TMP = Ax
        cblas_dgbmv( CblasColMajor, CblasNoTrans, *la, *la, *kl, *ku, 1, AA, *lab, X, 1, 0, TMP, 1);
        // TMP = TMP +  -RHS
        // TMP = Ax - B
        cblas_daxpy(*la, -1, RHS, 1, TMP, 1);
        norm_bmAx = cblas_dnrm2(*la, TMP, 1 );
        resvec[it] = norm_bmAx/norm_b;
    }

    *nbite = it;
    free(TMP);


}

void extract_MB_jacobi_tridiag(double *AB, double *MB, int *lab, int *la,
                               int *ku, int *kl, int *kv) {}

void extract_MB_gauss_seidel_tridiag(double *AB, double *MB, int *lab, int *la,
                                     int *ku, int *kl, int *kv) {}

void richardson_MB(double *AB, double *RHS, double *X, double *MB, int *lab,
                   int *la, int *ku, int *kl, double *tol, int *maxit,
                   double *resvec, int *nbite) {}
