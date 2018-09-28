CC = g++

all: main.o Game.o
	$(CC) -o main main.o Game.o

main.o: main.cpp Game.h
	$(CC) -c main.cpp -o main.o

Game.o: Game.cpp Game.h
	$(CC) -c Game.cpp -o Game.o

clean: 
	rm *.o main
