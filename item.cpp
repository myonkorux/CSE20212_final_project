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
	
	yOffset = 0;
	offsetDirection = 1;

}

void Item::display( SDL_Surface* object, SDL_Surface* destination )
{

	if ( offsetDirection == 1 ){
	
		if ( yOffset < 10 ){
		
			yOffset++;
		
		} else {
		
			offsetDirection = -1;
		
		}
	
	} else {
	
		if ( yOffset > 0 ){
		
			yOffset--;
		
		} else {
		
			offsetDirection = 1;
		
		}
	
	}

	SDL_Rect offset;

	offset.x = x;
	offset.y = y + yOffset;

	SDL_BlitSurface( object, NULL, destination, &offset );

}

int Item::getX()
{

	return x;

}

int Item::getY()
{

	return y;

}

int Item::getType()
{
	return type;
}

void Item::setX( int newx )
{

	x = newx;

}

void Item::setY( int newy )
{

	y = newy;

}

void Item::setType(int newType)
{

	type = newType;

}
