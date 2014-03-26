/******************

Chris Ray
Nathan Vahrenberg

box.h

*******************/

#include <iostream>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

using namespace std;

class Box{

	public:
		Box();
		void display();
		virtual void update() = 0;
	
	protected:
		int height;
		int width;
		int x;
		int y;

};
