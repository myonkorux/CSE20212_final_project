EXEC = main



$(EXEC): main.o board.o
	g++ main.o board.o -o $(EXEC)
	
main.o: main.cpp board.h
	g++ -c main.cpp

board.o: board.cpp board.h
	g++ -c board.cpp
