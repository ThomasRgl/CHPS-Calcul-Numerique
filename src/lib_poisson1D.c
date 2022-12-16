/**********************************************/
/* lib_poisson1D.c                            */
/* Numerical library developed to solve 1D    */
/* Poisson problem (Heat equation)            */
/**********************************************/
#include "lib_poisson1D.h"

void set_GB_operator_colMajor_poisson1D(double *AB, int *lab, int *la,
                                        int *kv) {
    
    // kv
    for( int k = 0; k < *kv; k++ ){
        for( int i = 0; i < *la; i++ ){
            AB[ k + i * (*lab) ] = 0;
        }
    }
    
    for( int i = 0; i < *la; i++ ){
            AB[ *kv + 0 + i * (*lab) ] = -1;
            AB[ *kv + 1 + i * (*lab) ] = 2;
            AB[ *kv + 2 + i * (*lab) ] = -1;
    }

    AB[ *kv ] = 0;
    AB[ (*lab) * (*la) - 1 ] = 0;

}

void set_GB_operator_colMajor_poisson1D_Id(double *AB, int *lab, int *la,
                                           int *kv) {}

void set_dense_RHS_DBC_1D(double *RHS, int *la, double *BC0, double *BC1) {
    
    RHS[ 0 ] = *BC0; 
    RHS[ *la - 1 ] = *BC1; 
    for( int i = 1; i < *la - 1; i++ ){
        RHS[ i ] = 0; 
    }
}

void set_analytical_solution_DBC_1D(double *EX_SOL, double *X, int *la,
                                    double *BC0, double *BC1) {
    for( int i = 0; i < *la; i++ ){
        EX_SOL[ i ] = *BC0 + X[ i ] * ( *BC1 - *BC0 ); 
    }
}

void set_grid_points_1D(double *x, int *la) {
    double step = 1.0f / ( *la + 1 );
    for( int i = 0; i < *la; i++ ){
        x[ i ] = 0 + (i + 1) * step; 
    }
}

void write_GB_operator_rowMajor_poisson1D(double *AB, int *lab, int *la,
                                          char *filename) {
    FILE *file;
    int ii, jj;
    file = fopen(filename, "w");
    // Numbering from 1 to la
    if (file != NULL) {
        for (ii = 0; ii < (*lab); ii++) {
            for (jj = 0; jj < (*la); jj++) {
                fprintf(file, "%lf\t", AB[ii * (*la) + jj]);
            }
            fprintf(file, "\n");
        }
        fclose(file);
    } else {
        perror(filename);
    }
}

void write_GB_operator_colMajor_poisson1D(double *AB, int *lab, int *la,
                                          char *filename) {
    FILE *file;
    int ii, jj;
    file = fopen(filename, "w");
    // Numbering from 1 to la
    if (file != NULL) {
        for (ii = 0; ii < (*la); ii++) {
            for (jj = 0; jj < (*lab); jj++) {
                fprintf(file, "%lf\t", AB[ii * (*lab) + jj]);
            }
            fprintf(file, "\n");
        }
        fclose(file);
    } else {
        perror(filename);
    }
}

void write_GB2AIJ_operator_poisson1D(double *AB, int *la, char *filename) {
    FILE *file;
    int jj;
    file = fopen(filename, "w");
    // Numbering from 1 to la
    if (file != NULL) {
        for (jj = 1; jj < (*la); jj++) {
            fprintf(file, "%d\t%d\t%lf\n", jj, jj + 1, AB[(*la) + jj]);
        }
        for (jj = 0; jj < (*la); jj++) {
            fprintf(file, "%d\t%d\t%lf\n", jj + 1, jj + 1, AB[2 * (*la) + jj]);
        }
        for (jj = 0; jj < (*la) - 1; jj++) {
            fprintf(file, "%d\t%d\t%lf\n", jj + 2, jj + 1, AB[3 * (*la) + jj]);
        }
        fclose(file);
    } else {
        perror(filename);
    }
}

void write_vec(double *vec, int *la, char *filename) {
    int jj;
    FILE *file;
    file = fopen(filename, "w");
    // Numbering from 1 to la
    if (file != NULL) {
        for (jj = 0; jj < (*la); jj++) {
            fprintf(file, "%lf\n", vec[jj]);
        }
        fclose(file);
    } else {
        perror(filename);
    }
}

void write_xy(double *vec, double *x, int *la, char *filename) {
    int jj;
    FILE *file;
    file = fopen(filename, "w");
    // Numbering from 1 to la
    if (file != NULL) {
        for (jj = 0; jj < (*la); jj++) {
            fprintf(file, "%lf\t%lf\n", x[jj], vec[jj]);
        }
        fclose(file);
    } else {
        perror(filename);
    }
}

int indexABCol(int i, int j, int *lab) { return 0; }

// kl, ku, n, info -> USELESS ?
int dgbtrftridiag(int *la, int *n, int *kl, int *ku, double *AB, int *lab,
                  int *ipiv, int *info) {

    double fact = 0.0f;
    for(int i = 1; i < *la ; i++){
        ipiv[i-1] = i; // ne pas oublier de set ipiv ! 

        // fact = bi / di
        fact = AB[ (*kl) + ( (*lab) * (i-1) ) + 2 ]  //b(i-1)
             / AB[ (*kl) + ( (*lab) * (i-1) ) + 1 ]; //a(i-1)

        AB[ (*kl) + ( (i-1) * (*lab)) + 2 ] = fact; // b(i-1) = fact

        AB[ (*kl) + ( i * (*lab)) + 1 ] =  // a(i) = a(i) - fact * c(i-1) -> c(i) is located at the i th  row of AB
            AB[ (*kl) + ( i * (*lab)) + 1 ] - 
            fact * AB[ (*kl) + ( i * (*lab)) + 0 ];
    }
    *info=0; 
    return *info;
}
