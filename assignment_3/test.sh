#!/bin/bash

echo "Assignment 3" && >&2 echo "Assignment 3" 
echo "Askisi 2" && >&2 echo "Askisi 2"

for i in {1..25}
do
    echo "Iteration $i" && >&2 echo "Iteration $i"
    ./askisi_2 100 100 1000 <data/100_100_1000.txt 
    ./askisi_2 200 200 4000 <data/200_200_4000.txt 
    ./askisi_2 300 300 9000 <data/300_300_9000.txt 
    ./askisi_2 400 400 16000 <data/400_400_16000.txt 
    ./askisi_2 500 500 25000 <data/500_500_25000.txt 
    ./askisi_2 600 600 36000 <data/600_600_36000.txt 
    ./askisi_2 700 700 49000 <data/700_700_49000.txt 
    ./askisi_2 800 800 64000 <data/800_800_64000.txt 
    ./askisi_2 900 900 81000 <data/900_900_81000.txt
    ./askisi_2 1000 1000 100000 <data/1000_1000_100000.txt 

done

echo "Askisi 3" && >&2 echo "Askisi 3"
for j in {1..10}
do
    export OMP_NUM_THREADS=$j
    echo "OMP_NUM_THREADS=$j" && >&2 echo "OMP_NUM_THREADS=$j"
    for i in {1..15}
    do
        echo "Iteration $i" && >&2 echo "Iteration $i"
        ./askisi_3 100 100 1000 <data/100_100_1000.txt 
        ./askisi_3 200 200 4000 <data/200_200_4000.txt 
        ./askisi_3 300 300 9000 <data/300_300_9000.txt 
        ./askisi_3 400 400 16000 <data/400_400_16000.txt 
        ./askisi_3 500 500 25000 <data/500_500_25000.txt 
        ./askisi_3 600 600 36000 <data/600_600_36000.txt 
        ./askisi_3 700 700 49000 <data/700_700_49000.txt 
        ./askisi_3 800 800 64000 <data/800_800_64000.txt 
        ./askisi_3 900 900 81000 <data/900_900_81000.txt
        ./askisi_3 1000 1000 100000 <data/1000_1000_100000.txt 
    done
done

echo "Done" && >&2 echo "Done"