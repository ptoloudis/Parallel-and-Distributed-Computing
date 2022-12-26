#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <complex.h>
 
float PI;
typedef float complex cplx;


void iterative_fft(cplx buf[], int size)
{
    unsigned int N = size , k = N, n;
	double thetaT = 3.14159265358979323846264338328L / N;
	cplx phiT = CMPLX(cos(thetaT), -sin(thetaT)), T;
    while (k > 1)
	{
		n = k;
		k >>= 1;
		phiT = phiT * phiT;
		T = 1.0L;
		for (unsigned int l = 0; l < k; l++)
		{
			for (unsigned int a = l; a < N; a += n)
			{
				unsigned int b = a + k;
				cplx t = buf[a] - buf[b];
				buf[a] += buf[b];
				buf[b] = t * T;
			}
			T *= phiT;
		}
    }
	// Decimate
	unsigned int m = (unsigned int)log2(N);
	for (unsigned int a = 0; a < N; a++)
	{
		unsigned int b = a;
		// Reverse bits
		b = (((b & 0xaaaaaaaa) >> 1) | ((b & 0x55555555) << 1));
		b = (((b & 0xcccccccc) >> 2) | ((b & 0x33333333) << 2));
		b = (((b & 0xf0f0f0f0) >> 4) | ((b & 0x0f0f0f0f) << 4));
		b = (((b & 0xff00ff00) >> 8) | ((b & 0x00ff00ff) << 8));
		b = ((b >> 16) | (b << 16)) >> (32 - m);
		if (b > a)
		{
			cplx t = buf[a];
			buf[a] = buf[b];
			buf[b] = t;
		}
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
	PI = 3.14159265;
	cplx buf[] = {1, 1, 1, 1, 0, 0, 0, 0};
 
	show("Data: ", buf);
	iterative_fft(buf, 8);
	show("\nFFT: ", buf);
 
	return 0;
}