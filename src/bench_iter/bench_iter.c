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


    run_benchmark("RA_TIME", alphaR, n, 0);
    run_benchmark("JACOBI_TIME", jacobi, n, 0);
    run_benchmark("GAUSS_TIME", gauss, n, 0);


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
    int maxit = 10;
    int nbite = 0;


    //
    f64 elapsed = 0.0;
    struct timespec t1, t2;
    f64 samples[MAX_SAMPLES];
    
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


    // Print header
    fprintf(fp,"%10s; %15s; %15s; %15s; %10s; %10s; %15s; %15s; %15s; %26s; %10s; %10s\n",
           "titre", "KiB", "MiB", "GiB", "n", "r", "min", "max", "mean",
           "stddev (%)", "MiB/s", "titre");

    for(int nn = 1; nn < 1+p; nn++){
        for(int jj = 0; jj < 2; jj++){
 
            int n = pow(2,nn+jj*0.5 );
            int laa = n;

            printf("%d\n",n);
            // la = n - 2;

            // Calculate the size of a single matrix
            u64 size = (sizeof(f64) * n * n);

            //
            f64 size_b = (float)size;
            f64 size_kib = size_b / (1024.0);
            f64 size_mib = size_b / (1024.0 * 1024.0);
            f64 size_gib = size_b / (1024.0 * 1024.0 * 1024.0);

   
            //
            for (u64 i = 0; i < MAX_SAMPLES; i++) {
       
                do {
                    for(int i = 0; i < laa; i++){SOL[i] = 0;}
                    for(int i = 0; i < laa; i++){TMP[i] = 0;}
                    set_grid_points_1D(X, &laa);
                    set_dense_RHS_DBC_1D(RHS, &laa, &T0, &T1);
                    set_analytical_solution_DBC_1D(EX_SOL, X, &laa, &T0, &T1);
                    set_GB_operator_colMajor_poisson1D(AB, &lab, &laa, &kv);
 
                    clock_gettime(CLOCK_MONOTONIC_RAW, &t1);

                    kernel( AB, RHS, ipiv, NRHS, laa, ku, kl, lab, maxit, resvec, 
                        TMP, &nbite, SOL, MB, tol, LU );

                    clock_gettime(CLOCK_MONOTONIC_RAW, &t2);

                    elapsed = (f64)(t2.tv_nsec - t1.tv_nsec) / (f64)1;//r;
                } while (elapsed <= 0.0);

                samples[i] = elapsed;
            }
            
            //
            sort_f64(samples, MAX_SAMPLES);

            //
            f64 min = samples[0];
            f64 max = samples[MAX_SAMPLES - 1];
            f64 mean = mean_f64(samples, MAX_SAMPLES);
            f64 dev = stddev_f64(samples, MAX_SAMPLES);

            // Size in MiB / time in seconds
            f64 mbps = size_mib / (mean / 1e9);

            //
            fprintf(fp,"%10s; %15.3lf; %15.3lf; %15.3lf; %10llu; %10llu; %15.3lf; %15.3lf; "
                   "%15.3lf; %15.3lf (%6.3lf %%); %10.3lf; %10s\n",
                   title,
                   size_kib,
                   size_mib, 
                   size_gib, 
                   n, r, min, max, mean, dev, (dev * 100.0 / mean), mbps, title);
        }
    }
        

    fclose(fp);
 
}
