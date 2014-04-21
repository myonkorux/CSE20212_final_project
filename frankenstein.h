/******************

Chris Ray
Nathan Vahrenberg

*******************/

#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <iostream>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

using namespace std;

class Frankenstein
{

	public:
		Frankenstein();
		void update( int, int );
		void display( SDL_Surface* );
		int attack( int, int );
		int isDead();
		void applyDamage(int);
		void Free_Memory();
		int getX();
		int getY();
		int getDirection();
	
	
	private:
		int x;
		int y;
		int health;
		int speed;
		int power;
		int xVel;
		int yVel;
		int direction;
		int isStanding;
		int isAttacking;
		int Dead;
		SDL_Surface* SpriteZombie;
		SDL_Rect moving[3];
		SDL_Rect attacking[3];
		SDL_Rect movingL[3];
		SDL_Rect attackingL[3];
		int clipSelect;

		SDL_Surface * optimizeImage(string);
	
};

#endif
