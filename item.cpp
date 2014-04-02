/******************

Chris Ray
Nathan Vahrenberg

item.cpp

*******************/

#include"item.h"

using namespace std;

// Constructor
Item::Item()
{

	//default values
	x = 0;
	y = 0;
	type = 0;
	

}

void Item::display( SDL_Surface* source, SDL_Surface* destination )
{

	SDL_Rect offset;

	offset.x = x;
	offset.y = y;

	SDL_BlitSurface( source, NULL, destination, &offset );

}

int Item::getx()
{

	return x;

}

int Item::gety()
{

	return y;

}

int Item::getType()
{
	return type;
}

void Item::setx( int newx )
{

	x = newx;

}

void Item::sety( int newy )
{

	y = newy;

}

void Item::setType(int newType)
{
	type = newType;
]
