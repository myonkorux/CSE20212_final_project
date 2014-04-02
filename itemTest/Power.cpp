#include"item.h"
#include"Power.h"

Power::Power(int newX, int newY, int newType)
{
	setX(newX);
	setY(newY);
	setType(newType);

	yOffset = 0;
	offsetDirection = 1;

	if(getType() >= 3)
	{
		PowerImage = loadImage("dot.bmp");
	}
}

void Power::display( SDL_Surface* object, SDL_Surface* destination )
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

	offset.x = getX();
	offset.y = getY() + yOffset;

	SDL_BlitSurface( object, NULL, destination, &offset );
}
