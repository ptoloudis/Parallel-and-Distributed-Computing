#!/bin/sh
# echo "stencil_1D_SEQ" >&2
# for k in 1 2 3
# do
#     for i in 1 2 3 4 5 6
#     do 
#         echo "Threads: $i" >&2
#         for j in 1 2 3 4 5 6 7 8 9 10
#         do
#             export OMP_NUM_THREADS=$i
#             F=$(($k*10000))
#             G=200000
#             ./stencil_1D_SEQ $F $G
#         done
#     done
# done

echo "\nstencil_2D_SEQ" >&2
# for k in 1 2 3
for k in 1 2
do 
    for i in 1 2 3 4 5 6
    do 
        echo "Threads: $i" >&2
        for j in 1 2 3 4 5 6 7 8 9 10
        do
            export OMP_NUM_THREADS=$i
            F=$(($k*1000))
            G=3000
            ./stencil_2D_SEQ $F $G
        done
    done
done


# echo "\nmat_vec_SEQ" >&2
# for k in 1 2 
# do
#     for z in 1 2 
#     do
#         echo $k $z >&2
#         for i in 1 2 3 4 5 6
#         do 
#             echo "Threads: $i" >&2
#             for j in 1 2 3 4 5 6 7 8 9 10
#             do
#                 F=$(($k*1000))
#                 G=$(($z*1000))
#                 ./mat_vec_SEQ $F $G
#             done
#         done
#     done
# done
