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

SDL_Surface * Item::loadImage(string filename)
{
	SDL_Surface* loadedImage = NULL;

	SDL_Surface* optimizedImage = NULL;

	loadedImage = IMG_Load( filename.c_str() );

	if( loadedImage != NULL )
	{
		optimizedImage = SDL_DisplayFormatAlpha( loadedImage );

		SDL_FreeSurface( loadedImage );

		if( optimizedImage != NULL )
		{
			Uint32 colorkey = SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF );

			SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, colorkey );
		}
	}

	return optimizedImage;
}
