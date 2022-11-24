#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

#define N 16

void *product_of_tables_1(float *a, float *b, float *sum)
{
    int i, j, l;
    for (i = 0; i < N; i++)
        for(j = 0; j < N; j++)
            for(l = 0; l < N; l++)
                sum[(i * N) + j] += a[(i * N) + l] * b[(l * N) + j];
        
    return NULL;
}

void *product_of_tables_2(float *a, float *b, float *sum)
{
    int i, j, l;
    for (i = 0; i < N; i+=2)
        for(j = 0; j < N; j+=2)
            for(l = 0; l < N; l++){
                sum[(i * N) + j] += a[(i * N) + l] * b[(l * N) + j];
                sum[(i * N) + j+1] += a[(i * N) + l] * b[(l * N) + j+1];
                sum[((i+1) * N) + j] += a[((i+1) * N) + l] * b[(l * N) + j];
                sum[((i+1) * N) + j+1] += a[((i+1) * N) + l] * b[(l * N) + j+1];
            }
    
    return NULL;
}


void *product_of_tables_3(float *a, float *b, float *sum)
{
    int i, j, l;
    for (i = 0; i < N; i+=4)
        for(j = 0; j < N; j+=4)
            for(l = 0; l < N; l++)
               for(int k1 = 0; k1 < 4; k1++)
                    for(int k2 = 0; k2 < 4; k2++)
                        sum[((i+k1) * N) + j+k2] += a[((i+k1) * N) + l] * b[(l * N) + j+k2];
    return NULL;
}


void *product_of_tables_4(float *a, float *b, float *sum)
{
    int i, j, l;
    for (i = 0; i < N; i+=8)
        for(j = 0; j < N; j+=8)
            for(l = 0; l < N; l++)
                for(int k1 = 0; k1 < 8; k1++)
                      for(int k2 = 0; k2 < 8; k2++)
                            sum[((i+k1) * N) + j+k2] += a[((i+k1) * N) + l] * b[(l * N) + j+k2];
    return NULL;
}


void *product_of_tables_5(float *a, float *b, float *sum)
{
    int i, j, l;
    for (i = 0; i < N; i+=16)
        for(j = 0; j < N; j+=16)
            for(l = 0; l < N; l++)
                for(int k1 = 0; k1 < 16; k1++)
                    for(int k2 = 0; k2 < 16; k2++)
                        sum[((i+k1) * N) + j+k2] += a[((i+k1) * N) + l] * b[(l * N) + j+k2];
    return NULL;
}


int main()
{
    srand(time(NULL));

    float *a, *b, *sum;

    float temp_a[N][N], temp_b[N][N], temp_sum[N][N];

    a = &temp_a[0][0];
    b = &temp_b[0][0];
    sum = &temp_sum[0][0];

     

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            temp_a[i][j] = ((float)rand()) / ((float)RAND_MAX) * 100;
            temp_b[i][j] = ((float)rand()) / ((float)RAND_MAX) * 100;
            temp_sum[i][j] = 0;
        }
    }

    clock_t start, end;
    double cpu_time_used, flops;
    float flop = (3*N) * pow(10, -6);

    start = clock();
    product_of_tables_1(a, b, sum);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    flops = flop/cpu_time_used;
    printf("Time for 1: %f, %f\n" , cpu_time_used, flops);
    sleep(1);

    start = clock();
    product_of_tables_2(a, b, sum);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;  
    flops = flop/cpu_time_used;
    printf("Time for 2: %f, %f\n" , cpu_time_used, flops);
    sleep(1);

    start = clock();
    product_of_tables_3(a, b, sum);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    flops = flop/cpu_time_used;
    printf("Time for 3: %f, %f\n" , cpu_time_used, flops);
    sleep(1);

    start = clock();
    product_of_tables_4(a, b, sum);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    flops = flop/cpu_time_used;
    printf("Time for 4: %f, %f\n" , cpu_time_used, flops);
    sleep(1);

    start = clock();
    product_of_tables_5(a, b, sum);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    flops = flop/cpu_time_used;
    printf("Time for 5: %f, %f\n" , cpu_time_used, flops);

    return 0;
}