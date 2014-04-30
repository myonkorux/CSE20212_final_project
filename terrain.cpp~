#include"terrain.h"
#include"item.h"

SDL_Surface * Terrain::optimizeImage(string filename)
{
	SDL_Surface * tempImage = NULL; 			//temporary surface to hold uploaded image
	SDL_Surface * optimized = NULL; 			//surface that will be output

	tempImage = IMG_Load(filename.c_str()); 		//loading the desired image

	if(tempImage != NULL) 					//this is here just in case there is an issue loading the image
	{
		optimized = SDL_DisplayFormat(tempImage); 	//optimized is now the uploaded image
		SDL_FreeSurface(tempImage); 			//freeing tempImage memory

		if( optimized != NULL ) 			//here just in case there was an issue with optimized
		{
		    Uint32 colorkey = SDL_MapRGB( optimized->format, 255, 255, 255 ); //this prevents white (color of terrain background) from being displayed
		    SDL_SetColorKey( optimized, SDL_SRCCOLORKEY, colorkey ); 	//this in effect creates a transparent background for the terrain
		}
	}

	return optimized;
}

Terrain::Terrain(int newX, int newY, int newType)
{
	setX(newX); 			//setting x and y coordinates type of terrain 
	setY(newY);
	setType(newType);

	if(getType() == 1) 		//type 1 corresponds to a rock
	{
		TerrainImage = optimizeImage("sprites/rock.bmp");
	}
	else if(getType() == 2) 	//type 2 corresponds to a tree
	{
		TerrainImage = optimizeImage("sprites/tree.bmp");
	}
}

void Terrain::display(SDL_Surface* destination )
{

	SDL_Rect offset;

	offset.x = getX(); 						//setting the coordinates for the source surface on the destination surface (the screen)
	offset.y = getY();

	SDL_BlitSurface( TerrainImage, NULL, destination, &offset ); 	//applying the clip of the source surface to the destination surface (the screen)

}

void Terrain::Free_Memory()
{
	SDL_FreeSurface(TerrainImage);
}
