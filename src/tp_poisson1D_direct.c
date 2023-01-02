/******************************************/
/* tp2_poisson1D_direct.c                 */
/* This file contains the main function   */
/* to solve the Poisson 1D problem        */
/******************************************/
#include "atlas_headers.h"
#include "lib_poisson1D.h"
#include <cblas.h>
#include <cblas_f77.h>
#include <lapack.h>
#include <lapacke.h>
#include <stdlib.h>

int main(int argc, char *argv[])
/* ** argc: Nombre d'arguments */
/* ** argv: Valeur des arguments */
{
    int ierr;
    int jj;
    int nbpoints, la;
    int ku, kl, kv, lab;
    int *ipiv;
    int info;
    int NRHS;
    double T0, T1;
    double *RHS, *EX_SOL, *X, *RES;
    double **AAB;
    double *AB;

    double temp, relres;

    NRHS = 1;
    nbpoints = 10;
    la = nbpoints - 2;
    T0 = -5.0;
    T1 = 5.0;

    printf("--------- Poisson 1D ---------\n\n");
    RHS = (double *)malloc(sizeof(double) * la);
    EX_SOL = (double *)malloc(sizeof(double) * la);
    RES = (double *)calloc(la, sizeof(double));
    X = (double *)malloc(sizeof(double) * la);

    // TODO : you have to implement those functions
    // DONE
    set_grid_points_1D(X, &la);
    set_dense_RHS_DBC_1D(RHS, &la, &T0, &T1);
    set_analytical_solution_DBC_1D(EX_SOL, X, &la, &T0, &T1);

    write_vec(RHS, &la, "data/RHS.dat");
    write_vec(EX_SOL, &la, "data/EX_SOL.dat");
    write_vec(X, &la, "data/X_grid.dat");

    kv = 1;
    ku = 1;
    kl = 1;
    lab = kv + kl + ku + 1;

    AB = (double *)malloc(sizeof(double) * lab * la);

    set_GB_operator_colMajor_poisson1D(AB, &lab, &la, &kv);
    // cblas_dgbmv( CblasColMajor, CblasNoTrans, la, la, kl, ku, 1, AB, lab, EX_SOL, 1, 0, RES, 1);

    // dgbmv();
    // dgbmv_(char *, const int32_t *, const int32_t *, const int32_t *, const int32_t *, const double *, const double *, const int32_t *, const double *, const int32_t *, const double *, double *, const int32_t *, size_t)
    
    double alpha = 1;
    double beta = 0;
    int ld = 4;
    const int32_t incx = 1;
    const int32_t incy = 1;

    cblas_dgbmv( CblasColMajor, CblasTrans, la, la, kl, ku, 1, AB+1, lab, EX_SOL, 1, 0, RHS, 1);
    //
    // dgbmv_("T", &la, &la, &kl, &ku, &alpha , AB+kv, &ld, EX_SOL, &incx, &beta, RES, &incy 
    // #ifdef LAPACK_FORTRAN_STRLEN_END
    //         ,0xdeadbeef
    // #endif
    // );

    // dgbmv_(N, la, kl, ku, const int32_t *, const double *, const double *, const int32_t *, const double *, const int32_t *, const double *, double *, const int32_t *, size_t)

    // dgbmv_("N", M, N, kl, ku, alpha, A, lda, x, incx, beta, y, incy, size_t)       
    // test_Poisson1D_dgbmv(&la , &kl, &ku, &lab, AB, EX_SOL, RES );

    write_vec(RHS, &la, "data/AxB.dat");
    write_GB_operator_colMajor_poisson1D(AB, &lab, &la, "data/AB.dat");
    
    printf("Solution with LAPACK\n");
    /* LU Factorization */
    info = 0;
    ipiv = (int *)calloc(la, sizeof(int));
    dgbtrf_(&la, &la, &kl, &ku, AB, &lab, ipiv, &info);

    /* LU for tridiagonal matrix  (can replace dgbtrf_) */
    // DONE
    //ierr = dgbtrftridiag(&la, &la, &kl, &ku, AB, &lab, ipiv, &info);

    write_GB_operator_colMajor_poisson1D(AB, &lab, &la, "data/LU.dat");

    /* Solution (Triangular) */
    if (info == 0) {
        // https://github.com/Reference-LAPACK/lapack/issues/512
        dgbtrs_("N", &la, &kl, &ku, &NRHS, AB, &lab, ipiv, RHS, &la, &info
        #ifdef LAPACK_FORTRAN_STRLEN_END
            ,0
        #endif
        );

        if (info != 0) {
            printf("\n INFO DGBTRS = %d\n", info);
        }
    } else {
        printf("\n INFO = %d\n", info);
    }

    /* It can also be solved with dgbsv */
    // TODO : use dgbsv
    // DONE
    //dgbsv_(&la, &ku, &kl, &NRHS, AB, &lab, ipiv, RHS, &la, &info);

    write_xy(RHS, X, &la, "data/SOL.dat");

    /* Relative forward error */
    // TODO : Compute relative norm of the residual
    // DONE
    // || x - xex || / || xex ||
    // || RHS - EX_SOL || / || EX_SOL ||
    double norm_EX_SOL = cblas_dnrm2(la, EX_SOL, 1 );

    // using daxpy for RHS = -1 * EX_SOL + RHS
    cblas_daxpy(la, -1, EX_SOL, 1, RHS, 1);
    write_vec(RHS, &la, "data/DIFF.dat");
    double norm_absolute = cblas_dnrm2(la, RHS, 1 );
    relres = norm_absolute / norm_EX_SOL;



    printf("\nThe relative forward error is relres = %e\n", relres);

    free(RHS);
    free(RES);
    free(EX_SOL);
    free(X);
    free(AB);
    printf("\n\n--------- End -----------\n");
}
