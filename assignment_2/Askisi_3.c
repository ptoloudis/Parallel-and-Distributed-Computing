// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <math.h>
// #include <time.h>
// #include <complex.h>
// #include <omp.h> 

// typedef float complex cplx;

// void iterative_fft(cplx buf[], int size)
// {
//     unsigned int N = size , k = N, n;
// 	double thetaT = 3.14159265358979323846264338328L / N;
// 	cplx phiT = CMPLX(cos(thetaT), -sin(thetaT)), T;
// 	#pragma omp parallel
// 	{
// 		while (k > 1)
// 		{
// 			n = k;
// 			k >>= 1;
// 			phiT = phiT * phiT;
// 			T = 1.0L;
			
// 			for (unsigned int l = 0; l < k; l++)
// 			{
// 				#pragma omp for
// 				for (unsigned int a = l; a < N; a += n)
// 				{
// 					unsigned int b = a + k;
// 					cplx t = buf[a] - buf[b];
// 					buf[a] += buf[b];
// 					buf[b] = t * T;
// 				}
// 				T *= phiT;
// 			}
// 		}
// 		// Decimate
// 		unsigned int m = (unsigned int)log2(N);
		
// 		#pragma omp for
// 		for (unsigned int a = 0; a < N; a++)
// 		{
// 			unsigned int b = a;
// 			// Reverse bits
// 			b = (((b & 0xaaaaaaaa) >> 1) | ((b & 0x55555555) << 1));
// 			b = (((b & 0xcccccccc) >> 2) | ((b & 0x33333333) << 2));
// 			b = (((b & 0xf0f0f0f0) >> 4) | ((b & 0x0f0f0f0f) << 4));
// 			b = (((b & 0xff00ff00) >> 8) | ((b & 0x00ff00ff) << 8));
// 			b = ((b >> 16) | (b << 16)) >> (32 - m);
// 			if (b > a)
// 			{
// 				cplx t = buf[a];
// 				buf[a] = buf[b];
// 				buf[b] = t;
// 			}
// 		}
// 	}
// }

// void show(const char * s, cplx buf[]) {
// 	printf("%s", s);
// 	for (int i = 0; i < 8; i++)
// 		if (!cimag(buf[i]))
// 			printf("%g ", creal(buf[i]));
// 		else
// 			printf("(%g, %g) ", creal(buf[i]), cimag(buf[i]));
// }

// int main(int argc, char *argv[])
// {
// // 	PI = 3.14159265;
// // 	cplx buf[] = {1, 1, 1, 1, 0, 0, 0, 0};
// // 	clock_t start, end;
	
// // 	show("Data: ", buf);
// // 	start = clock();
// // 	iterative_fft(buf, 8);
// // 	end = clock();
// // 	printf("time: %f", (double)(end - start) / CLOCKS_PER_SEC);
// // 	show("\nFFT: ", buf);
 
// 	cplx *buf;
// 	int i = 10,size;
// 	clock_t start, end;

// 	// if (argc != 2) {
// 	// 	printf("Usage: %s <number of elements>\n", argv[0]);
// 	// 	exit(1);
// 	// }
// 	// i = atoi(argv[1]);

// 	size = pow(2,i);
// 	buf = (cplx *)malloc(size * sizeof(cplx));
// 	for (int i = 0; i < size; i++)
// 		buf[i] = rand() % 100;


// 	printf("elements: %d ", i);
// 	fflush(stdout);

// 	start = clock();
// 	iterative_fft(buf, size);
// 	end = clock();
// 	printf("time: %f\n", (double)(end - start));

// 	// free(buf);

// 	return 0;
// }

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
#pragma omp parallel for
    for (int i = 0; i < n; i++)
        R[i] = X[i];
    
#pragma omp for
    for (int m = 0; m < r; m++){
        for(int i=0; i<n; i++)
            S[i] = R[i];
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

// int main()
// {
// 	PI = 3.14159265;
// 	cplx buf[] = {1, 1, 1, 1, 0, 0, 0, 0};
//     cplx buf2[] = {1, 1, 1, 1, 0, 0, 0, 0};
 
// 	show("Data: ", buf);
// 	fft(buf, buf2, 8);
// 	show("\nFFT: ", buf2);
 
// 	return 0;
// }
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