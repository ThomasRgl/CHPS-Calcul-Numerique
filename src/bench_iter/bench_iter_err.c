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
                void kernel( double *restrict AB, double *restrict RHS,
                            int *restrict ipiv, int NRHS, int la, int ku,
                            int kl, int lab, int maxit, double * resvec, 
                            double * TMP, int * nbite, double * SOL,
                            double * MB, double tol, double * LU ),
                   u64 p, u64 r);

//
int main(int argc, char **argv) {
    //
    srand(getpid());

    //
    if (argc < 2)
        return printf("usage: %s [n]\n", argv[0]), 1;
    // Number of array elements
    u64 n = atoll(argv[1]);


    run_benchmark("RA_IT", alphaR, n, 0);
    run_benchmark("JACOBI_IT", jacobi, n, 0);
    run_benchmark("GAUSS_IT", gauss, n, 0);

    //
    return 0;
}

//
void run_benchmark(const char *title,
                void kernel( double *restrict AB, double *restrict RHS,
                            int *restrict ipiv, int NRHS, int la, int ku,
                            int kl, int lab, int maxit, double * resvec, 
                            double * TMP, int * nbite, double * SOL,
                            double * MB, double tol, double * LU ),
                   u64 p, u64 r){
    //
    FILE *fp;
    char filename[50] = "data/";
    strcat(filename, title);
    strcat(filename, ".dat");

    fp = fopen(filename,"wr");

    //////////////////////////////////////////////////////////

    int ierr, jj, nbpoints, la, ku, kl, lab, kv,info, NRHS;
    double T0, T1;
    double temp, relres ;
    int *ipiv;
    double *RHS, *SOL, *EX_SOL, *X, *AB, *MB, *LU, *resvec, *TMP;

    u64 base = 2;
    la = base * pow(2,p);

    NRHS = 1;
    // nbpoints = 12;
    // la = nbpoints - 2;

    T0 = 5.0;
    T1 = 20.0;

    kv = 0;
    ku = 1;
    kl = 1;
    lab = kv + kl + ku + 1;

    double tol = 1e-10;
    int maxit = 10000;
    int nbite = 0;



    //////////////////////////////////////////////////////////

    RHS    = (double *)malloc(sizeof(double) * la);
    EX_SOL = (double *)malloc(sizeof(double) * la);
    X      = (double *)malloc(sizeof(double) * la);
    AB     = (double *)malloc(sizeof(double) * lab * la);
    LU     = (double *)malloc(la * lab * sizeof(double));
    MB     = (double *)malloc(sizeof(double) * (lab)*la);
    resvec = (double *)calloc(maxit, sizeof(double));
    TMP    = (double *)calloc(la, sizeof(double));
    ipiv   = (int *)   calloc(la, sizeof(int));
    SOL    = (double *)calloc(la, sizeof(double));

    //////////////////////////////////////////////////////////

   
    //////////////////////////////////////////////////////////

    for(int nn = 1; nn < 1+p; nn++){
        for(int jj = 0; jj < 10; jj++){
   
        int laa = pow(2,nn+jj*0.1 );
        nbite = 0;
        for(int i = 0; i < laa; i++){SOL[i] = 0;}
        for(int i = 0; i < laa; i++){TMP[i] = 0;}
        set_grid_points_1D(X, &laa);
        set_dense_RHS_DBC_1D(RHS, &laa, &T0, &T1);
        set_analytical_solution_DBC_1D(EX_SOL, X, &laa, &T0, &T1);
        set_GB_operator_colMajor_poisson1D(AB, &lab, &laa, &kv);


        kernel( AB, RHS, ipiv, NRHS, laa, ku, kl, lab, maxit, resvec, 
            TMP, &nbite, SOL, MB, tol, LU );

        // printf("%d %d\n", laa, nbite);
        fprintf(fp,"%d; %lf\n", laa, resvec[nbite] );
        }
    }

    /////////////////////////////////////////////////////////
    
sortie:

    free(RHS    );
    free(EX_SOL );
    free(X      );
    free(AB     );
    free(LU     );
    free(MB     );
    free(resvec );
    free(TMP    );
    free(ipiv   );
    free(SOL    );
    
    fclose(fp);




   //  // Print header
   //  fprintf(fp,"%10s; %15s; %15s; %15s; %10s; %10s; %15s; %15s; %15s; %26s; %10s; %10s\n",
   //         "titre", "KiB", "MiB", "GiB", "n", "r", "min", "error_av", "error_ar",
   //         "stddev (%)", "MiB/s", "titre");
   //
   //
   //
   //  for(int nn = 6; nn < 6+p; nn++){
   //      for(int jj = 0; jj < 10; jj++){
   //
   //      int n = pow(2,nn+jj*0.1 );
   //  
   //      u64 size = (sizeof(f64) * n * n);
   //
   //      //
   //      f64 size_b = (float)size;
   //      f64 size_kib = size_b / (1024.0);
   //      f64 size_mib = size_b / (1024.0 * 1024.0);
   //      f64 size_gib = size_b / (1024.0 * 1024.0 * 1024.0);
   //
   // 
   //      //
   //      fprintf(fp,"%10s; %15.3lf; %15.3lf; %15.3lf; %10llu; %10llu; %15.3lf; "
   //              "%15.3le; %15.3le;"
   //              " %15.3lf (%6.3lf %%); %10.3lf; %10s\n",
   //             title,
   //             size_kib,
   //             size_mib, 
   //             size_gib, 
   //             (u64)n, r, 0.f, err_av, err_arr, 0.f, 0.f, 0.f, title);
   //      }
   //  }
   //      
   //
   //  fclose(fp);

}
