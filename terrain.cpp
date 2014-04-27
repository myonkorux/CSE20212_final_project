#include"terrain.h"
#include"item.h"

SDL_Surface * Terrain::optimizeImage(string filename)
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

Terrain::Terrain(int newX, int newY, int newType)
{
	setX(newX);
	setY(newY);
	setType(newType);

	if(getType() == 1)
	{
		TerrainImage = optimizeImage("sprites/rock.bmp");
	}
	else if(getType() == 2)
	{
		TerrainImage = optimizeImage("sprites/tree.bmp");
	}
}

void Terrain::display(SDL_Surface* destination )
{

	SDL_Rect offset;

	offset.x = getX();
	offset.y = getY();

	SDL_BlitSurface( TerrainImage, NULL, destination, &offset );

}

void Terrain::Free_Memory()
{
	SDL_FreeSurface(TerrainImage);
}
