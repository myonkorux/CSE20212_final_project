/******************

Chris Ray
Nathan Vahrenberg

item.h

*******************/

#include <iostream>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

using namespace std;

class Item{

	public:
		Item();
		void display();
		virtual void update() = 0;
		int getx();
		int gety();
	
	protected:
		int x;
		int y;

};
