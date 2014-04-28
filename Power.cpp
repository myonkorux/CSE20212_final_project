#include <cmath>
#include"item.h"
#include"Power.h"

Power::Power(int newX, int newY, int newType)
{
	setX(newX);
	setY(newY);
	setType(newType);

	yOffset = 0.0;
	t = 0.0;
	PowerImage = optimizeImage("sprites/powerups.bmp");
}

SDL_Surface * Power::optimizeImage(string filename)
{
	SDL_Surface * tempImage = NULL;
	SDL_Surface * optimized = NULL;

	tempImage = IMG_Load(filename.c_str());

	if(tempImage != NULL)
	{
		optimized = SDL_DisplayFormat(tempImage);
		SDL_FreeSurface(tempImage);

		if( optimized != NULL )
		{
		    Uint32 colorkey = SDL_MapRGB( optimized->format, 255, 255, 255 );
		    SDL_SetColorKey( optimized, SDL_SRCCOLORKEY, colorkey );
		}
	}

	return optimized;
}

void Power::display(SDL_Surface* destination )
{
	yOffset = 8*sin( t );
	t += 0.1;
	if (t >= 2*M_PI){
		t = 0;
	}

	SDL_Rect offset;

	offset.x = getX();
	offset.y = getY() + yOffset;

	chooseImage();

	SDL_BlitSurface( PowerImage, &clip, destination, &offset );
}

void Power::cleanImage()
{
	SDL_FreeSurface(PowerImage);
}

void Power::chooseImage()
{
	if(getType() == 1)
	{
		clip.x = 0;
		clip.w = 50;
		clip.y = 0;
		clip.h = 50;
	}
	else if(getType() == 4)
	{
		clip.x = 50;
		clip.w = 50;
		clip.y = 0;
		clip.h = 50;
	}
	else if(getType() == 2)
	{
		clip.x = 0;
		clip.w = 50;
		clip.y = 50;
		clip.h = 50;
	}
	else
	{
		clip.x = 50;
		clip.w = 50;
		clip.y = 50;
		clip.h = 50;
	}
}
