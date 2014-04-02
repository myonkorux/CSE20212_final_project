#include"terrain.h"
#include"item.h"

Terrain::Terrain(int newX, int newY, int newType)
{
	setx(newX);
	sety(newY);
	setType(newType);

	if(getType() == 1)
	{
		TerrainImage = loadImage("rock2f.png");
	}
	else if(getType() == 2)
	{
		TerrainImage = loadImage("tree.png");
	}
}

void Terrain::display( SDL_Surface* object, SDL_Surface* destination )
{

	SDL_Rect offset;

	offset.x = x;
	offset.y = y;

	SDL_BlitSurface( object, NULL, destination, &offset );

}
