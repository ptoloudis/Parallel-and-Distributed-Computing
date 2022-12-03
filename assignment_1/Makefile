
CFLAGS = -Wall -Wextra -Werror -g

Askisi2:  
	gcc $(CFLAGS) Askisi_2.c -o askisi2 

Askisi3:  
	gcc $(CFLAGS) Askisi_3.c -o askisi3

Askisi5:
	mpicc -Wall Askisi_5.c -o askisi5

run_all: clean Askisi2 Askisi3 Askisi5

clean:
	rm -f askisi2
	rm -f askisi3
	rm -f askisi5