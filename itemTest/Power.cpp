#include"item.h"
#include"Power.h"

Power::Power(int newX, int newY, int newType)
{
	setx(newX);
	sety(newY);
	setType(newType);

	yOffset = 0;
	offsetDirection = 1;

	if(getType() >= 3)
	{
		TerrainImage = loadImage("dot.bmp");
	}
}

void Power::display( SDL_Surface* object, SDL_Surface* destination )
{

	SDL_Rect offset;

	offset.x = x;
	offset.y = y;

	SDL_BlitSurface( object, NULL, destination, &offset );

}
