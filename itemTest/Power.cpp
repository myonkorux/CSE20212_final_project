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

	if(getType() >= 3)
	{
		PowerImage = loadImage("dot.bmp");
	}
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

	SDL_BlitSurface( PowerImage, NULL, destination, &offset );
}

void Power::cleanImage()
{
	SDL_FreeSurface(PowerImage);
}
