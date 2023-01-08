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
    if (argc < 3)
        return printf("usage: %s [n] [r]\n", argv[0]), 1;

    // Number of array elements
    u64 n = atoll(argv[1]);

    // Number of kernel repetitions
    u64 r = atoll(argv[2]);

    run_benchmark("DGBTRF-S", a, n, r);
    run_benchmark("MANUEL", b, n, r);
    run_benchmark("DGBSV", c, n, r);

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
    f64 elapsed = 0.0;
    struct timespec t1, t2;
    f64 samples[MAX_SAMPLES];
    

    //
    u64 base = 64;
    int nbpoints, la;
    int ku, kl, kv, lab;
    int *ipiv;
    int info;
    int NRHS;
    double T0, T1;
    double *RHS, *EX_SOL, *X, *RES, *AB;

    //
    NRHS = 1;
    la = base * pow(2,p);
    T0 = -5.0;
    T1 = 5.0;

    kv = 1;
    ku = 1;
    kl = 1;
    lab = kv + kl + ku + 1;
    info = 0;
 


    //    
    RHS = (double *)malloc(sizeof(double) * la);
    // EX_SOL = (double *)malloc(sizeof(double) * la);
    // RES = (double *)calloc(la, sizeof(double));
    // X = (double *)malloc(sizeof(double) * la);
    AB = (double *)malloc(sizeof(double) * lab * la);
    ipiv = (int *)calloc(la, sizeof(int));


    // Print header
    fprintf(fp,"%10s; %15s; %15s; %15s; %10s; %10s; %15s; %15s; %15s; %26s; %10s; %10s\n",
           "titre", "KiB", "MiB", "GiB", "n", "r", "min", "max", "mean",
           "stddev (%)", "MiB/s", "titre");



    for(int n = base; n < la; n=n*2){
        printf("%d\n",n);
        // la = n - 2;

        // Calculate the size of a single matrix
        u64 size = (sizeof(f64) * n * n);

        //
        f64 size_b = (float)size;
        f64 size_kib = size_b / (1024.0);
        f64 size_mib = size_b / (1024.0 * 1024.0);
        f64 size_gib = size_b / (1024.0 * 1024.0 * 1024.0);

        // set_dense_RHS_DBC_1D(RHS, &la, &T0, &T1);
        // set_GB_operator_colMajor_poisson1D(AB, &lab, &la, &kv);
   
        //
        for (u64 i = 0; i < MAX_SAMPLES; i++) {
       
            do {
                set_dense_RHS_DBC_1D(RHS, &n, &T0, &T1);
                set_GB_operator_colMajor_poisson1D(AB, &lab, &n, &kv);

                clock_gettime(CLOCK_MONOTONIC_RAW, &t1);

                //for (u64 j = 0; j < r; j++)
                    // kernel(a, b, c, n);
                    kernel( AB, RHS, ipiv, NRHS, n, ku, kl, lab );

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
        

        fclose(fp);

        //
        free(RHS);
        // free(RES);
        // free(EX_SOL);
        // free(X);
        free(AB);
        free(ipiv);
 
}
