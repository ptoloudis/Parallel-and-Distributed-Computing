#include <fftw3.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>
#include <time.h>

int main()
{
    
    int N = pow(2, 12);
    clock_t start, end;
    int m;
    
    start = clock();
    
    // create pointers
    fftw_complex    *in;
    fftw_complex    *out;
    fftw_plan       testPlan;

    // preallocate vectors for FFTW
    in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);

    // create FFTW plan
    testPlan = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
    
    for (m = 0; m < 36; m++) {
        // execute plan
        fftw_execute(testPlan);
    }

    // fftw_print_plan(testPlan);

    // clean up
    fftw_free(in);
    fftw_free(out);
    fftw_destroy_plan(testPlan);
    

    end = clock();
    printf("Time taken: %f", (double)(end - start));

}