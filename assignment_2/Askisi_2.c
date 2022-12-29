/*********************************
 * Ergasia 2 – Askhsh 2  
 * Eponymo Onoma : Apostolopoulou Ioanna
 * - AEM: 03121
 * Eponymo Onoma : Toloudis Panagiotis
 * - AEM: 02995
 *********************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <complex.h>

float PI;
typedef float complex cplx;
 
void _fft(cplx buf[], cplx out[], int n, int step)
{
	if (step < n) {
		_fft(out, buf, n, step * 2);
		_fft(out + step, buf + step, n, step * 2);
 
		for (int i = 0; i < n; i += 2 * step) {
			cplx t = cexp(-I * PI * i / n) * out[i + step];
			buf[i / 2]     = out[i] + t;
			buf[(i + n)/2] = out[i] - t;
		}
	}
}
 
void fft(cplx buf[], int n)
{
	cplx out[n];
	for (int i = 0; i < n; i++) 
		out[i] = buf[i];
 
	_fft(buf, out, n, 1);
}
 
 
// void show(const char * s, cplx buf[]) {
// 	printf("%s", s);
// 	for (int i = 0; i < 8; i++)
// 		if (!cimag(buf[i]))
// 			printf("%g ", creal(buf[i]));
// 		else
// 			printf("(%g, %g) ", creal(buf[i]), cimag(buf[i]));
// }

// int main()
// {
// 	PI = 3.14159265;
// 	cplx buf[] = {1, 1, 1, 1, 0, 0, 0, 0};
 
// 	show("Data: ", buf);
// 	fft(buf, 8);
// 	show("\nFFT: ", buf);
 
// 	return 0;
// }


int main()
{
	srand(time(NULL));
	PI = 3.14159265;
	cplx *buf;
	int i,size;
	clock_t start, end;

	for(i=10; i<20; i++){
		size = pow(2,i);
		buf = (cplx *)malloc(size * sizeof(cplx));
		for (int i = 0; i < size; i++)
			buf[i] = rand() % 100;

		printf("elements: %d\n", i);

		for(int j=0; j<15; j++){
			start = clock();
			fft(buf, size);
			end = clock();
			printf("time: %f\n", (double)(end - start));
		}
		free(buf);
	}
 
	return 0;
}