CC = gcc
CCFLAGS = -Wall -g 
OBJ = askisi_2.o askisi_3.o 


askiseis: $(OBJ)
	$(CC) askisi_2.o -o askisi_2
	$(CC) askisi_3.o -o askisi_3 -fopenmp

askisi_2.o: askisi_2.c header.h
	$(CC) $(CCFLAGS) -c $<

askisi_3.o: askisi_3.c header.h
	$(CC) $(CCFLAGS) -c $< -fopenmp
clean:
	rm -f *.o 