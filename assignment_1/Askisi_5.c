/*********************************
 * Ergasia 1 – Askhsh 4  
 * Eponymo Onoma : Apostolopoulou Ioanna
 * - AEM: 03121
 * Eponymo Onoma : Toloudis Panagiotis
 * - AEM: 02995
 *********************************/

// Program that calculates the product of 1D stencil

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

#define SIZE 100000

int main() 
{ 
    

    int size, rank, i, size_1;
    clock_t start, end;
    double cpu_time_used; 

    start = clock();
    MPI_Init(NULL, NULL);

    int *array, *array_1;
    int *data, *data_1;
    
    int product, dot_product;
    int color;

    MPI_Comm_size(MPI_COMM_WORLD, &size);   // Get the number of threads
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // Rank of the thread running the code
    MPI_Comm row_comm;                    // Communicator for the row

    if(rank == 0)
        color = 0;
    else 
        color = 1;
        
    MPI_Comm_split(MPI_COMM_WORLD, color, rank, &row_comm);// creating communicator for barrier

    if(rank == 0){
    	srand(0);

        dot_product = 0;
        product = 0;

    	array = (int*)calloc(SIZE, sizeof(int));
    	array_1 = (int*)calloc(SIZE, sizeof(int));

    	for(i = 0; i < SIZE; i++){
    		array[i] = (rand() % 10) + 1; 
    		array_1[i] = (rand() % 10) + 1;
    	}

    	size_1 = SIZE / size; // dividing elements among the threads.

    	data = (int*)calloc(size_1, sizeof(int));
    	data_1 = (int*)calloc(size_1, sizeof(int));

        // Splits data for cpmputing dot product
    	MPI_Scatter(array, size_1, MPI_INT, data, size_1, MPI_INT, 0, MPI_COMM_WORLD);
    	MPI_Scatter(array_1, size_1, MPI_INT, data_1, size_1, MPI_INT, 0, MPI_COMM_WORLD);

        for(i = 0; i < size_1; i++)
            product += data[i] * data_1[i];

        // Gathers the data from all computations
        MPI_Reduce(&product, &dot_product, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    	// printf("\ndot product is %d\n", dot_product);
	}
    else
    {
		size_1 = SIZE / size;
		product = 0;

    	data = (int*)calloc(size_1, sizeof(int));
    	data_1 = (int*)calloc(size_1, sizeof(int));

        // Splits data for cpmputing dot product
    	MPI_Scatter(array, size_1, MPI_INT, data,size_1, MPI_INT, 0, MPI_COMM_WORLD);
    	MPI_Scatter(array_1, size_1, MPI_INT, data_1, size_1, MPI_INT, 0, MPI_COMM_WORLD);
       
        for(i = 0; i < size_1; i++)
    		product += data[i] * data_1[i];

        MPI_Barrier(row_comm);

        // Gathers the data from all computations
        MPI_Reduce(&product, &dot_product, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

        // printf("\nmy rank :%d and product:%d\n",rank,product);
	}

    MPI_Finalize();

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time taken: %f\n", cpu_time_used);
    return 0;
}