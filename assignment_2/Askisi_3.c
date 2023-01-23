#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <complex.h>
#include <omp.h> 

float PI;
typedef float complex cplx;

void fft(cplx X[], cplx Y[], int n)
{
    int r;
    cplx *R, *S;

    r = log2(n);
    R = (cplx *)malloc(n * sizeof(cplx));
    S = (cplx *)malloc(n * sizeof(cplx));
    for (int i = 0; i < n; i++)
        R[i] = X[i];
    
#pragma omp parallel for
    for (int m = 0; m < r; m++){
        for(int i=0; i<n; i++)
            S[i] = R[i];
#pragma omp parallel for
        for(int i=0; i<n; i++){
            int k = (i & ~(1 << m)) | (1 << m);
            int j = (i & ~(1 << m));
            R[i] = S[j] + S[k] * cpow(cexp(-2 * PI * I * i / n),m);
            // printf("i=%d, j=%d, k=%d, m=%d\n",i,j,k,m);
        }

    }

#pragma omp for
    for (int i = 0; i < n; i++){
        int ii = 0;
        /*(b0b1b2...br-1) η δυαδική αναπαράσταση του i 
        θα γίνει (br-1b2b1b0) η δυαδική αναπαράσταση του ii*/
        for (int j = 0; j < r; j++)
            ii = ii | ((i >> j) & 1) << (r - j - 1);
        Y[i] = R[ii];
    }
}

void show(const char * s, cplx buf[]) {
	printf("%s", s);
	for (int i = 0; i < 8; i++)
		if (!cimag(buf[i]))
			printf("%g ", creal(buf[i]));
		else
			printf("(%g, %g) ", creal(buf[i]), cimag(buf[i]));
}

int main()
{
	srand(time(NULL));
	PI = 3.14159265;
	cplx *buf, *buf2;
	int i=10,size;
	clock_t start, end;

	for(i=10; i<20; i++){
		size = pow(2,i);
		buf = (cplx *)malloc(size * sizeof(cplx));
        buf2 = (cplx *)malloc(size * sizeof(cplx));
		for (int i = 0; i < size; i++){
			buf[i] = rand() % 100;
            buf2[i] = 0;
        }

		printf("elements: %d\n", i);

		for(int j=0; j<15; j++){
			start = clock();
			fft(buf, buf2, size);
			end = clock();
			printf("time: %f\n", (double)(end - start));
		}
		free(buf);
	}
 
	return 0;
}