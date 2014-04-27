#ifndef TERRAIN_H
#define TERRAIN_H

#include "item.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

class Terrain : public Item
{
	public:
		Terrain(int, int, int);
		void display(SDL_Surface *);
		int getX();
		int getY();
		void Free_Memory();
		
	private:
		SDL_Surface * TerrainImage;
		SDL_Surface * optimizeImage(string);
};


#endif
