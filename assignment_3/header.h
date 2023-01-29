/*********************************
 * Ergasia 3 – Askhsh 2 , 3 
 * Eponymo Onoma : Apostolopoulou Ioanna
 * - AEM: 03121
 * Eponymo Onoma : Toloudis Panagiotis
 * - AEM: 02995
 *********************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Sparse_CSR 
{
    int n_rows;
    int n_cols;
    int n_nz;
    int* row_ptrs;
    int* col_indices;
    double* values;
} Sparse_CSR_t;


int print_sparse_csr(const Sparse_CSR_t* A_csr) 
{
    printf("row\tcol\tval\n");
    printf("----\n");

    for (int i=0; i<A_csr->n_rows; ++i) {
        int nz_start = A_csr->row_ptrs[i];
        int nz_end = A_csr->row_ptrs[i+1];

        for (int nz_id=nz_start; nz_id<nz_end; ++nz_id) {
            int j = A_csr->col_indices[nz_id];
            double val = A_csr->values[nz_id];
            printf("%d\t%d\t%02.2f\n", i, j, val);
        }
    }
    return EXIT_SUCCESS;
}

int free_sparse_csr(Sparse_CSR_t* A_csr) 
{
    free(A_csr->row_ptrs);
    free(A_csr->col_indices);
    free(A_csr->values);

    return EXIT_SUCCESS;
}