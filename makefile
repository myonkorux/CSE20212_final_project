EXEC = main

$(EXEC): testMain.o board.o box.o item.o unit.o player.o zombie.o text.o button.o counter.o
	g++ testMain.o board.o box.o item.o unit.o player.o zombie.o text.o button.o counter.o -o $(EXEC) -g -lSDL -lSDL_image -lSDL_ttf
	
testMain.o: testMain.cpp board.h
	g++ -c -g testMain.cpp

board.o: board.cpp board.h
	g++ -c -g board.cpp
	
box.o: box.cpp box.h
	g++ -c -g box.cpp -std=c++0x
	
item.o: item.cpp item.h
	g++ -c -g item.cpp
	
unit.o: unit.cpp unit.h
	g++ -c -g unit.cpp
	
player.o: player.cpp player.h
	g++ -c -g player.cpp -lSDL -lSDL_image
	
zombie.o: zombie.cpp zombie.h
	g++ -c -g zombie.cpp -lSDL -lSDL_image

text.o:  text.cpp text.h
	g++ -c -g text.cpp

button.o:  button.cpp button.h
	g++ -c -g button.cpp

counter.o:  counter.cpp counter.h
	g++ -c -g counter.cpp
	
clean:
	rm -f core* $(EXEC) *.o
