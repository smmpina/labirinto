CFLAGS = -std=c11 -Wall -pedantic

lab: labirinto.o newlib.o brws.o menuh.o
	gcc -o lab *.o -lm

labirinto.o: labirinto.c
	gcc $(CFLAGS) -c labirinto.c

newlib.o: newlib.c
	gcc $(CFLAGS) -c newlib.c

brws.o: brws.c
	gcc $(CFLAGS) -c brws.c

menuh.o: menuh.c
	gcc $(CFLAGS) -c menuh.c

run:
	./lab

clean:
	rm -rf lab *.o
