#ifndef TERRAIN_H
#define TERRAIN_H

#include"item.h"

class Terrain : public Item
{
	public:
		Terrain(int, int, int);
		void display(SDL_Surface *, SDL_Surface *);
	private:
		SDL_Surface * TerrainImage;
		
};


#endif
