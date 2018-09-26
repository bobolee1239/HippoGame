all: main.o Game.o
	g++ -o main main.o Game.o

main.o: main.cpp Game.h
	g++ -c main.cpp -o main.o

Game.o: Game.cpp Game.h
	g++ -c Game.cpp -o Game.o

clean: 
	rm *.o main
