#!/bin/bash
echo "\nAskisi 3"

for i in 1 2 3 4 5 6 7 8 9 10
do 
    echo "\nThreads: $i"
    export OMP_NUM_THREADS=$i
    ./askisi3
done
