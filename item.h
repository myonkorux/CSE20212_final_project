/******************

Chris Ray
Nathan Vahrenberg

item.h

*******************/

#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include<iomanip>
#include<string>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

using namespace std;

class Item
{
	public:
		Item();
		void display(SDL_Surface *, SDL_Surface *);
		int getX();
		int getY();
		int getType();
		void setX( int );
		void setY( int );
		void setType(int);
	
	private:
		int x;
		int y;
		int type;
		int yOffset;          // Used for
		int offsetDirection;  // float effect

};

#endif
