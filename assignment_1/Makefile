
CFLAGS = -Wall -Wextra -Werror -g

Askisi2:  
	gcc $(CFLAGS) Askisi_2.c -o askisi2 

Askisi3:  
	gcc $(CFLAGS) Askisi_3.c -o askisi3

run_askisi2:
	for number in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20; do \
        echo $$number ; \
		./askisi2 ; \
    done

run_askisi3: 
	for number in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20; do \
        echo $$number ; \
		./askisi3 ; \
    done

run_all: clean Askisi2 Askisi3 run_askisi2 run_askisi3

clean:
	rm -f askisi2
	rm -f askisi3