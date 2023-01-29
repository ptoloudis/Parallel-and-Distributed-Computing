/*********************************
 * Ergasia 3 – Askhsh 4  
 * Eponymo Onoma : Apostolopoulou Ioanna
 * - AEM: 03121
 * Eponymo Onoma : Toloudis Panagiotis
 * - AEM: 02995
 *********************************/



//
// Implementation of the iterative Jacobi method.
//
// Given a known, diagonally dominant matrix A and a known vector b, we aim to
// to find the vector x that satisfies the following equation:
//
//     Ax = b
//
// We first split the matrix A into the diagonal D and the remainder R:
//
//     (D + R)x = b
//
// We then rearrange to form an iterative solution:
//
//     x' = (b - Rx) / D
//
// We can then iterate this solution until it converges to the solution x.

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>
#include "header.h"

#define N 10000
#define MAX_ITERATIONS 20
#define CONVERGENCE_THRESHOLD 0.0001

int create_sparse_csr(const double* A, int n_rows, int n_cols, int n_nz, Sparse_CSR_t *A_csr) 
{
    int nz_id = 0;

    A_csr->n_rows = n_rows;
    A_csr->n_cols = n_cols;
    A_csr->n_nz = n_nz;

    A_csr->row_ptrs = calloc(n_rows+1, sizeof(int));
    A_csr->col_indices = calloc(n_nz, sizeof(int));
    A_csr->values = calloc(n_nz, sizeof(double));

    for (int i = 0; i < n_rows; i++) 
    {
        A_csr->row_ptrs[i] = nz_id;
        for (int j = 0; j < n_cols; j++) 
        {
            if (A[(i * n_cols) + j] != 0.0) 
            {
                A_csr->col_indices[nz_id] = j;
                A_csr->values[nz_id] = A[(i * n_cols) + j];
                nz_id++;
            }
        }
        
    }
    A_csr->row_ptrs[n_rows] = nz_id;

    return EXIT_SUCCESS;
}

int matrix_vector_sparse_csr(const Sparse_CSR_t* A_csr, const double* vec, double* res) 
{
    #pragma omp parallel 
    #pragma omp for
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

// Make the tridiagonal matrix -1 2 -1
void make_tridiagonal(double *A, int n)
{
  int i, j;

  for (i = 0; i < n; i++)
  {
    for (j = 0; j < n; j++)
    {
      if (i == j)
        A[i * n + j] = 2.0;
      else if (i == j + 1 || i == j - 1)
        A[i * n + j] = -1.0;
      else
        A[i * n + j] = 0.0;
    }
  }
}


// Run the Jacobi solver
// Returns the number of iterations performed
int run(const Sparse_CSR_t *A_csr, double *b, double *x, double *xtmp)
{
  int itr, row;
  double res[N] = {0.0};
  double dot;
  double diff;
  double sqdiff = 1 , hdiff, sqhdiff;
  double *ptrtmp;

  // Loop until converged or maximum iterations reached
  for(itr = 0; itr < MAX_ITERATIONS && (sqrt(sqdiff) > CONVERGENCE_THRESHOLD); itr++)
  {
    // Perfom Jacobi iteration
    #pragma omp parallel for private(dot)
    for (row = 0; row < A_csr->n_rows; row++)
    {
      dot = 0.0;
      int nz_start = A_csr->row_ptrs[row];
      int nz_end = A_csr->row_ptrs[row+1];
      #pragma omp parallel for reduction(+:dot)
      for (int nz_id = nz_start; nz_id < nz_end; ++nz_id) {
        int j = A_csr->col_indices[nz_id];
        double val = A_csr->values[nz_id];
        if (nz_id == 0 || (row != 0 && (nz_start + 1) == nz_id))
          continue;
        else
          dot += val * x[j];
      }
      if(row != 0)
        xtmp[row] = (b[row] - dot) / A_csr->values[nz_start+1];
      else
        xtmp[row] = (b[row] - dot) / A_csr->values[nz_start];
    }

    // Swap pointers
    ptrtmp = x;
    x      = xtmp;
    xtmp   = ptrtmp;

    // Check for convergence
    sqdiff = 0.0;
    sqhdiff = 0.0;
    matrix_vector_sparse_csr(A_csr, x, res);
    #pragma omp parallel for reduction(+:sqdiff) reduction(+:sqhdiff)
    for (row = 0; row < A_csr->n_rows; row++)
    {
      hdiff   = b[row] - res[row];
      sqhdiff += hdiff * hdiff;
      diff    = xtmp[row] - x[row];
      sqdiff += diff * diff;
    }

    printf("Iter=%d, residual=%.2f, diff=%.2f\n", itr, sqrt(sqhdiff) , sqrt(sqdiff));

  }

  return itr;
}


double get_timestamp()
{
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_sec + tv.tv_usec*1e-6;
}


int main(int argc, char *argv[])
{
  double total_runtime;
  
  double *A    = malloc(N*N*sizeof(double));
  double *b    = malloc(N*sizeof(double));
  double *x    = malloc(N*sizeof(double));
  double *xtmp = malloc(N*sizeof(double));

  
  printf("Matrix size:            %dx%d\n", N, N);
  printf("Maximum iterations:     %d\n", MAX_ITERATIONS);
  printf("Convergence threshold:  %lf\n", CONVERGENCE_THRESHOLD);
  

  // Initialize data
  int nz = 3*N-2;
  make_tridiagonal(A, N);
  Sparse_CSR_t* A_csr = malloc(sizeof(Sparse_CSR_t));
  create_sparse_csr(A, N, N, nz, A_csr);
  
  for (int row = 0; row < N; row++)
  {
    b[row] = row;
    x[row] = 0.0;
  }

  // Run Jacobi solver
  double solve_start = get_timestamp();
  int itr = run(A_csr, b, x, xtmp);
  double solve_end = get_timestamp();

  total_runtime = solve_end - solve_start;

  // Check error of final solution
  double err = 0.0;
  for (int row = 0; row < N; row++)
  {
    double tmp = 0.0;
    for (int col = 0; col < N; col++)
    {
      tmp += A[row + col*N] * x[col];
    }
    tmp = b[row] - tmp;
    err += tmp*tmp;
  }
  err = sqrt(err);

  printf("Solution error = %lf\n", err);
  printf("Iterations     = %d\n", itr);
  printf("Solver runtime = %lf seconds\n", total_runtime);
  if (itr == MAX_ITERATIONS)
    printf("WARNING: solution did not converge\n");

  free(A);
  free(b);
  free(x);
  free(xtmp);

  return 0;
}
