#inicio makefile

all: server clean

trabalho: trabalho.o mastermind.o database.o
	gcc trabalho.o mastermind.o database.o -o trabalho

trabalho.o: trabalho.c
	gcc -c trabalho.c
        
mastermind.o: mastermind.c
	gcc -c mastermind.c
        
database.o: database.c
	gcc -c database.c

server: server.o database.o mastermind.o
	gcc server.o database.o mastermind.o -o server

server.o: server.c
	gcc -c server.c

clean:
	rm *.o
