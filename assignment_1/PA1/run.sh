#!/bin/sh

for k in 1 2 3 4 5
do
    for z in 1 2 3 4 5
    do
        echo "\nRunning $k $z"
 
        for i in 1 2 3 4 5
        do 
            for j in 1 2 3 4 5 6 7 8 9 10
            do
                echo "NUM_THREADS:"$i " LOOPS:"$j 
                export OMP_NUM_THREADS=$i

                echo "stencil_1D_SEQ"
                F=$(($k*10000))
                G=$(($z*200000))
                ./stencil_1D_SEQ $F $G

                echo "\nstencil_2D_SEQ"
                F=$(($k*3000))
                G=$(($z*3000))
                ./stencil_2D_SEQ $F $G

                echo "\nmat_vec_SEQ"
                F=$(($k*25000))
                G=$(($z*10000))
                ./mat_vec_SEQ $F $G
            done
        done
    done
done