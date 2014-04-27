EXEC = main

$(EXEC): testMain.o board.o box.o item.o Power.o unit.o player.o zombie.o axebaby.o frankenstein.o text.o button.o counter.o terrain.o
	g++ testMain.o board.o box.o item.o Power.o unit.o player.o zombie.o axebaby.o frankenstein.o text.o button.o counter.o terrain.o -o $(EXEC) -g -lSDL -lSDL_image -lSDL_ttf
	
testMain.o: testMain.cpp board.h
	g++ -c -g testMain.cpp

board.o: board.cpp board.h
	g++ -c -g board.cpp
	
box.o: box.cpp box.h
	g++ -c -g box.cpp -std=c++0x
	
item.o: item.cpp item.h
	g++ -c -g item.cpp

Power.o:  Power.cpp Power.h item.h
	g++ -c -g Power.cpp
	
unit.o: unit.cpp unit.h
	g++ -c -g unit.cpp
	
player.o: player.cpp player.h
	g++ -c -g player.cpp 
	
zombie.o: zombie.cpp zombie.h
	g++ -c -g zombie.cpp 

axebaby.o: axebaby.cpp axebaby.h
	g++ -c -g axebaby.cpp 
	
frankenstein.o: frankenstein.cpp frankenstein.h
	g++ -c -g frankenstein.cpp 

text.o:  text.cpp text.h
	g++ -c -g text.cpp

button.o:  button.cpp button.h
	g++ -c -g button.cpp

counter.o:  counter.cpp counter.h
	g++ -c -g counter.cpp
	
terrain.o:  terrain.cpp terrain.h
	g++ -c -g terrain.cpp
	
clean:
	rm -f core* $(EXEC) *.o
