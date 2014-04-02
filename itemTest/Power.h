#ifndef POWERUP_H
#define POWERUP_H

#include"Power.h"

class Power : public Item
{
	public:
		Power(int, int ,int);
		void display(SDL_Surface *, SDL_Surface *);
	private:
		SDL_Surface * powerImage;
		int yOffset;          // Used for
		int offsetDirection;  // float effect
			
};

#endif
