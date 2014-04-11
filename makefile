EXEC = main

$(EXEC): main.o board.o box.o item.o unit.o player.o
	g++ main.o board.o box.o item.o unit.o player.o -o $(EXEC) -lSDL -lSDL_image -lSDL_ttf
	
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
	
player.o: player.cpp player.h unit.h
	g++ -c player.cpp -lSDL -lSDL_image
	
clean:
	rm -f *.o
	rm $(EXEC)
