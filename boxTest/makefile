all:  boxTest

boxTest:  main.o text.o box.o button.o counter.o
	g++ -o boxTest -g main.o text.o box.o button.o counter.o -lSDL -lSDL_image -lSDL_ttf

main.o:  main.cpp text.h
	g++ -c -g main.cpp

text.o:  text.cpp text.h
	g++ -c -g text.cpp

box.o:  box.cpp box.h
	g++ -c -g box.cpp -std=c++0x

button.o:  button.cpp button.h
	g++ -c -g button.cpp

counter.o:  counter.cpp counter.h
	g++ -c -g counter.cpp

clean:
	rm -f core* boxTest *.o
