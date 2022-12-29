CC=gcc
CFLAGS=-O3 -fopenmp -Wall

.PHONY: all
all: mc_serial mc_parallel

mc_serial: mc_serial.c
	$(CC) $(CFLAGS) -o mc_serial mc_serial.c -lm

mc_parallel: mc_parallel.c
	$(CC) $(CFLAGS) -o mc_parallel mc_parallel.c -lm

.PHONY: clean
clean:
	rm -f mc_serial mc_parallel
