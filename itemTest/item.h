/******************

Chris Ray
Nathan Vahrenberg

item.h

*******************/

#include <iostream>
#include<iomanip>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

using namespace std;

class Item
{

	public:
		Item();
		void display(SDL_Surface *, SDL_Surface *);
		virtual void update() = 0;
		int getx();
		int gety();
		int getType();
		void setx( int );
		void sety( int );
		void setType(int);
	
	protected:
		int x;
		int y;
		int type;

};
