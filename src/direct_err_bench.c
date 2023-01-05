//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

//

//
#include "tools.h"
#include "types.h"

//
#include "kernel.h"

//
#define ALIGN64 64

//
#define MAX_SAMPLES 33

//
void run_benchmark(const char *title,
                   void (*kernel)( double *restrict, double *restrict, int *restrict, 
                           int NRHS, int la, int ku, int kl, int lab ),
                   u64 n, u64 r);

//
int main(int argc, char **argv) {
    //
    srand(getpid());

    //
    if (argc < 2)
        return printf("usage: %s [n]\n", argv[0]), 1;

    // Number of array elements
    u64 n = atoll(argv[1]);


    run_benchmark("ERR_DGBTRF-S", a, n, 0);
    run_benchmark("ERR_MANUEL", b, n, 0);
    run_benchmark("ERR_DGBSV", c, n, 0);

    //
    return 0;
}

//
void run_benchmark(const char *title,
                   void (*kernel)( double *restrict, double *restrict, int *restrict, 
                           int NRHS, int la, int ku, int kl, int lab ),
                   u64 p, u64 r){

    //
    FILE *fp;
    char filename[50] = "data/";
    strcat(filename, title);
    strcat(filename, ".dat");

    fp = fopen(filename,"wr");

    

    //
    u64 base = 64;
    int nbpoints, la;
    int ku, kl, kv, lab, ld;
    int *ipiv;
    int info;
    int NRHS;
    double T0, T1;
    double *RHS, *EX_SOL, *X, *RES, *AB, *ABX;

    double err_av, err_arr = 0.0f;

    //
    NRHS = 1;
    la = base * pow(2,p);
    T0 = -5.0;
    T1 = 5.0;

    ld = 4;
    kv = 1;
    ku = 1;
    kl = 1;
    lab = kv + kl + ku + 1;
    info = 0;
 


    //    
    RHS = (double *)malloc(sizeof(double) * la);
    EX_SOL = (double *)malloc(sizeof(double) * la);
    // RES = (double *)calloc(la, sizeof(double));
    X = (double *)malloc(sizeof(double) * la);
    AB = (double *)malloc(sizeof(double) * lab * la);
    ABX = (double *)malloc(sizeof(double)  * la);
    ipiv = (int *)calloc(la, sizeof(int));


    // Print header
    fprintf(fp,"%10s; %15s; %15s; %15s; %10s; %10s; %15s; %15s; %15s; %26s; %10s; %10s\n",
           "titre", "KiB", "MiB", "GiB", "n", "r", "min", "error_av", "error_ar",
           "stddev (%)", "MiB/s", "titre");



    for(int nn = 6; nn < 6+p; nn++){
        for(int jj = 0; jj < 10; jj++){

        int n = pow(2,nn+jj*0.1 );
        // printf("%d \n",nn);
        // printf("%d \n",jj);
        printf("%d \n",n);

        // la = n - 2;

        // Calculate the size of a single matrix
        u64 size = (sizeof(f64) * n * n);

        //
        f64 size_b = (float)size;
        f64 size_kib = size_b / (1024.0);
        f64 size_mib = size_b / (1024.0 * 1024.0);
        f64 size_gib = size_b / (1024.0 * 1024.0 * 1024.0);

   
        // erreur avant
        set_grid_points_1D(X, &n);
        set_dense_RHS_DBC_1D(RHS, &n, &T0, &T1);
        set_GB_operator_colMajor_poisson1D(AB, &lab, &n, &kv);
        set_analytical_solution_DBC_1D(EX_SOL, X, &n, &T0, &T1);

        kernel( AB, RHS, ipiv, NRHS, n, ku, kl, lab );
        
        f64 norm_EX_SOL = cblas_dnrm2(n, EX_SOL, 1 );
        cblas_daxpy(n, -1, EX_SOL, 1, RHS, 1);
        f64 norm_absolute = cblas_dnrm2(n, RHS, 1 );
        err_av = norm_absolute / norm_EX_SOL;
       

        // erreur arriere
        set_grid_points_1D(X, &n);
        set_dense_RHS_DBC_1D(RHS, &n, &T0, &T1);
        set_GB_operator_colMajor_poisson1D(AB, &lab, &n, &kv);
        set_analytical_solution_DBC_1D(EX_SOL, X, &la, &T0, &T1);
        kernel( AB, RHS, ipiv, NRHS, n, ku, kl, lab );
        
        
        f64 norm_X = cblas_dnrm2(n, RHS, 1 );
        f64 norm_A = cblas_dnrm2(n, AB, 1 );
        cblas_dgbmv( CblasColMajor, CblasNoTrans, n, n, kl, ku, 1, AB, ld, RHS, 1, 0, ABX, 1);
        set_dense_RHS_DBC_1D(RHS, &n, &T0, &T1);
        cblas_daxpy(n, -1, RHS, 1, ABX, 1);
        f64 norm_abs = cblas_dnrm2( n, ABX, 1 );
        err_arr = ( norm_abs ) / ( norm_X * norm_A );
       

        
        //

        //

        // Size in MiB / time in seconds

        //
        fprintf(fp,"%10s; %15.3lf; %15.3lf; %15.3lf; %10llu; %10llu; %15.3lf; "
                "%15.3le; %15.3le;"
                " %15.3lf (%6.3lf %%); %10.3lf; %10s\n",
               title,
               size_kib,
               size_mib, 
               size_gib, 
               (u64)n, r, 0.f, err_av, err_arr, 0.f, 0.f, 0.f, title);
        }
    }
        

        fclose(fp);

        //
        free(RHS);
        // free(RES);
        // free(EX_SOL);
        // free(X);
        free(AB);
        free(ipiv);
}
