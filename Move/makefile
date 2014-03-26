all:  Move

Move:  moveMain.o Screen.o 
	g++ -o Move moveMain.o Screen.o -lSDL -lSDL_image

moveMain.o:  moveMain.cpp
	g++ -c moveMain.cpp

Screen.o:  Screen.h Screen.cpp
	g++ -c Screen.cpp


clean:
	rm -f core* Move moveMain.o Screen.o *.o
