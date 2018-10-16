all: mastermind clean

mastermind: mastermind.o 
	gcc mastermind.o -o mastermind

mastermind.o: mastermind.c
	gcc -c mastermind.c

clean:
	rm *.o
