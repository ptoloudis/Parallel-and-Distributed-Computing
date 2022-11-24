#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


#define N 220

float  internal_dot_product_step_1(float  *a, float  *b)
{
    int i;
    float sum = 0;
    for (i = 0; i < N; i++)
        sum += a[i] * b[i];
    return sum;
}

float  internal_dot_product_step_2(float  *a, float  *b)
{
    int i;
    float sum = 0;
    for (i = 0; i < N; i+=2)
        sum += a[i] * b[i] + a[i+1] * b[i+1];
    return sum;
}

float  internal_dot_product_step_3(float  *a, float  *b)
{
    int i;
    float sum = 0;
    for (i = 0; i < N; i+=4)
        sum += a[i] * b[i] + a[i+1] * b[i+1] + a[i+2] * b[i+2] + a[i+3] * b[i+3];
    return sum;
}

float internal_dot_product_step_4(float  *a, float  *b)
{
    int i;
    float sum = 0;
    for (i = 0; i < N - 8; i+=8)
        sum += a[i] * b[i] + a[i+1] * b[i+1] + a[i+2] * b[i+2] + a[i+3] * b[i+3] + a[i+4] * b[i+4] + a[i+5] * b[i+5] + a[i+6] * b[i+6] + a[i+7] * b[i+7];
    sum += a[i] * b[i] + a[i+1] * b[i+1] + a[i+2] * b[i+2] + a[i+3] * b[i+3];
    return sum;
}

float internal_dot_product_step_5(float  *a, float  *b)
{
    int i;
    float sum = 0;
    for (i = 0; i < N - 16; i+=16)
        sum += a[i] * b[i] + a[i+1] * b[i+1] + a[i+2] * b[i+2] + a[i+3] * b[i+3] + a[i+4] * b[i+4] + a[i+5] * b[i+5] + a[i+6] * b[i+6] + a[i+7] * b[i+7] + a[i+8] * b[i+8] + a[i+9] * b[i+9] + a[i+10] * b[i+10] + a[i+11] * b[i+11] + a[i+12] * b[i+12] + a[i+13] * b[i+13] + a[i+14] * b[i+14] + a[i+15] * b[i+15];
    sum += a[i] * b[i] + a[i+1] * b[i+1] + a[i+2] * b[i+2] + a[i+3] * b[i+3] + a[i+4] * b[i+4] + a[i+5] * b[i+5] + a[i+6] * b[i+6] + a[i+7] * b[i+7] + a[i+8] * b[i+8] + a[i+9] * b[i+9] + a[i+10] * b[i+10] + a[i+11] * b[i+11] ;
    return sum;
}




int main()
{
    int i;
    float  *a, *b, sum;
    clock_t start, end;
    double cpu_time_used;

    srand(time(NULL));

    a = (float *)malloc(N * sizeof(int));
    b = (float *)malloc(N * sizeof(int));

    for (i = 0; i < N; i++)
    {
        a[i] = ((float)rand() / (float)(RAND_MAX)) * 1000;
        b[i] = ((float)rand() / (float)(RAND_MAX)) * 1000;
    }

    float flop = 440 * pow(10, -6);

    start = clock();
    sum = internal_dot_product_step_1(a, b);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Step 1: %f, %f, %f\n", sum, cpu_time_used, flop/cpu_time_used);

    start = clock();
    sum = internal_dot_product_step_2(a, b);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Step 2: %f, %f, %f\n", sum, cpu_time_used, flop/cpu_time_used);


    start = clock();
    sum = internal_dot_product_step_3(a, b);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Step 3: %f, %f, %f\n", sum, cpu_time_used, flop/cpu_time_used);


    start = clock();
    sum = internal_dot_product_step_4(a, b);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Step 4: %f, %f, %f\n", sum, cpu_time_used, flop/cpu_time_used);


    start = clock();
    sum = internal_dot_product_step_5(a, b);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Step 5: %f, %f, %f\n", sum, cpu_time_used, flop/cpu_time_used);


    free(a);
    free(b);
    return 0;
}