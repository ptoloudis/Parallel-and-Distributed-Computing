
CFLAGS = -Wall -g

all: clean Askisi2 Askisi3

Askisi2:  
	gcc $(CFLAGS) Askisi_2.c -o askisi2 -lm

Askisi3:  
	gcc $(CFLAGS) Askisi_3.c -o askisi3 -lm -fopenmp

myfftw:
	gcc myfftw.c -o myfftw -lm -lfftw3

clean:
	rm -f askisi2
	rm -f askisi3