#ifndef TERRAIN_H
#define TERRAIN_H

#include"item.h"

class Terrain : public Item
{
	public:
		Terrain(int, int, int);
		void display(SDL_Surface *);
		void cleanImage();
	private:
		SDL_Surface * TerrainImage;
		
};


#endif
