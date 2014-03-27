EXEC = main

$(EXEC): main.o board.o box.o item.o unit.o
	g++ main.o board.o box.o item.o unit.o -o $(EXEC)
	
main.o: main.cpp board.h
	g++ -c main.cpp

board.o: board.cpp board.h
	g++ -c board.cpp
	
box.o: box.cpp box.h
	g++ -c box.cpp
	
item.o: item.cpp item.h
	g++ -c item.cpp
	
unit.o: unit.cpp unit.h
	g++ -c unit.cpp
	
clean:
	rm -f *.o
	rm $(EXEC)
