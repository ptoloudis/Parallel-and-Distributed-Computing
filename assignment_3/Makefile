CC = gcc
CCFLAGS = -Wall -g 

askiseis:
	$(CC) $(CCFLAGS) askisi_2.c -o askisi_2 header.h
	$(CC) $(CCFLAGS) askisi_3.c -o askisi_3 header.h -fopenmp
	$(CC) $(CCFLAGS) askisi_4.c -o askisi_4 header.h -fopenmp -lm

test: askiseis
	./test.sh

clean:
	rm -f askisi_2 askisi_3 askisi_4