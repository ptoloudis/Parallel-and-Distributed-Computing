/*********************************
 * Ergasia 3 – Askhsh 2  
 * Eponymo Onoma : Apostolopoulou Ioanna
 * - AEM: 03121
 * Eponymo Onoma : Toloudis Panagiotis
 * - AEM: 02995
 *********************************/
 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "header.h"

int create_sparse_csr(const double* A, int n_rows, int n_cols, int n_nz, Sparse_CSR_t* A_csr) 
{
    A_csr->n_rows = n_rows;
    A_csr->n_cols = n_cols;
    A_csr->n_nz = n_nz;
    A_csr->row_ptrs = calloc(n_rows+1, sizeof(int));
    A_csr->col_indices = calloc(n_nz, sizeof(int));
    A_csr->values = calloc(n_nz, sizeof(double));

    int nz_id = 0;

    for (int i=0; i<n_rows; ++i) 
    {
        A_csr->row_ptrs[i] = nz_id;
        for (int j=0; j<n_cols; ++j) 
        {
            if (A[i*n_cols + j] != 0.0) 
            {
                A_csr->col_indices[nz_id] = j;
                A_csr->values[nz_id] = A[i*n_cols + j];
                nz_id++;
            }
        }
        
    }

    A_csr->row_ptrs[n_rows] = nz_id;

    return EXIT_SUCCESS;
}

int matrix_vector_sparse_csr(const Sparse_CSR_t* A_csr, const double* vec, double* res) 
{
    for (int i=0; i<A_csr->n_rows; ++i) {
        res[i] = 0.0;
        int nz_start = A_csr->row_ptrs[i];
        int nz_end = A_csr->row_ptrs[i+1];
        for (int nz_id=nz_start; nz_id<nz_end; ++nz_id) {
            int j = A_csr->col_indices[nz_id];
            double val = A_csr->values[nz_id];
            res[i] = res[i] + val * vec[j];
        }
    }
    return EXIT_SUCCESS;
}

int main (int argc, char** argv) 
{
    int n_rows, n_cols, n_nz;
    if (argc == 4)
    {
        n_rows = atoi(argv[1]);
        n_cols = atoi(argv[2]);
        n_nz = atoi(argv[3]);
    } 
    else
    {
        printf("Usage: %s N M nz\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    double *A  = (double*) malloc(n_rows * n_cols * sizeof(double));
    double *x  = (double*) malloc(n_cols * sizeof(double));
    double *Ax = (double*) malloc(n_cols * sizeof(double));
    
    for (int i=0; i<n_rows; ++i) 
    {
        x[i] = 1.0;
    }

    int rows, cols;
    double val;
    A = calloc(n_rows*n_cols, sizeof(double));
    for (size_t k = 0; k < n_nz; k++)
    {
        scanf("%d %d %lf", &rows, &cols, &val);
        rows--;
        cols--;
        A[rows*n_cols + cols] = val;
    }   
    
    // Starts here
    Sparse_CSR_t A_csr;

    create_sparse_csr(A, n_rows, n_cols, n_nz, &A_csr);

    // print_sparse_csr(&A_csr);

    clock_t start = clock();
    matrix_vector_sparse_csr(&A_csr, x, Ax);
    clock_t end = clock();
    double time_spent = (double)(end - start);
    printf("Time spent: %f\n", time_spent);
    // for (int i=0; i<n_rows; ++i) 
    // {
    //     printf("%02.2f\n", Ax[i]);
    // }

    free(A);
    free(x);
    free(Ax);
    free_sparse_csr(&A_csr);

    return EXIT_SUCCESS;
}

