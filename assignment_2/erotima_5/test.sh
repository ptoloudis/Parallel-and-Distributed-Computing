#!/bin/bash
for i in 1 2 3 4 5 6 7 8 9 10
do 
    ./mc_serial 1672503689  
done

echo "\nParallel"
for i in 1 2 3 4 5 6 7 8 9 10
do 
    echo "\nThreads: $i"
    export OMP_NUM_THREADS=$i
    for j in 1 2 3 4 5 6 7 8 9 10
    do 
        ./mc_parallel 1672503689 
    done
done

