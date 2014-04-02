#ifndef POWER_H
#define POWER_H

#include"Power.h"

class Power : public Item
{
	public:
		Power(int, int ,int);
		void display(SDL_Surface *);
		void cleanImage();
	private:
		SDL_Surface * PowerImage;
		int yOffset;          // Used for
		int offsetDirection;  // float effect
			
};

#endif