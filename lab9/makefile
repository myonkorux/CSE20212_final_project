all:  menu

menu:  menuMain.o Menu.o
	g++ -o menu menuMain.o Menu.o -lSDL -lSDL_image -lSDL_ttf

menuMain.o:  Menu.h menuMain.cpp
	g++ -c menuMain.cpp

Menu.o:  Menu.h Menu.cpp
	g++ -c Menu.cpp -std=c++0x

clean:
	rm -f core* menu *.o
