# !/bin/sh

# /*********************************
#  * Ergasia 1 – Askhsh 4  
#  * Eponymo Onoma : Apostolopoulou Ioanna
#  * - AEM: 03121
#  * Eponymo Onoma : Toloudis Panagiotis
#  * - AEM: 02995
#  *********************************/

echo"\nRunning Makefile"
make
cd PA1
make
cd ..
echo "\nMakefile Finished"

# echo "\nRunning Tests"

# echo"\nAskisi 2"
# for number in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
# do 
#     echo $$number 
#     ./askisi2 
# done

# echo"\nAskisi 3"
# for number in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
# do 
#     echo $$number 
#     ./askisi3 
# done

# echo"\nAskisi 4"
# echo"\nstencil_1D_SEQ"
# for k in 1 2 3
# do
#     for i in 1 2 3 4 5 6
#     do 
#         echo"\nThreads: $i"
#         for j in 1 2 3 4 5 6 7 8 9 10
#         do
#             export OMP_NUM_THREADS=$i
#             F=$(($k*10000))
#             G=200000
#             ./PA1/PA1/stencil_1D_SEQ $F $G
#         done
#     done
# done

# echo"\nstencil_2D_SEQ" 
# for k in 1 2 3
# do 
#     for i in 1 2 3 4 5 6
#     do 
#         echo"\nThreads: $i" 
#         for j in 1 2 3 4 5 6 7 8 9 10
#         do
#             export OMP_NUM_THREADS=$i
#             F=$(($k*1000))
#             G=3000
#             ./PA1/stencil_2D_SEQ $F $G
#         done
#     done
# done


# echo"\nmat_vec_SEQ"
# for k in 1 2 
# do
#     for z in 1 2 
#     do
#         echo $k $z
#         for i in 1 2 3 4 5 6
#         do 
#             echo"\nThreads: $i"
#             for j in 1 2 3 4 5 6 7 8 9 10
#             do
#                 F=$(($k*1000))
#                 G=$(($z*1000))
#                 ./PA1/mat_vec_SEQ $F $G
#             done
#         done
#     done
# done


# echo "\nAskisi 5"
# for i in 1 2 3 4
# do
#     echo"\nThreads: $i"
#     for number in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
#     do
#         mpirun -np $i ./askisi5
#     done
# done

# echo "\nTests Finished"