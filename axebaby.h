/******************

Chris Ray
Nathan Vahrenberg

*******************/

#ifndef AXEBABY_H
#define AXEBABY_H

#include <iostream>
#include<iomanip>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

using namespace std;

class Axebaby
{

	public:
		Axebaby();
		void update( int, int );
		void display( SDL_Surface* );
		int attack( int, int );
		int isDead();
		void applyDamage(int);
		void Free_Memory();
		int getX();
		int getY();
		int getDirection();
		int getPoints();
	
	
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
		int points;
		SDL_Surface* SpriteAxebaby;
		SDL_Rect moving[4];
		SDL_Rect attacking[1];
		SDL_Rect movingL[4];
		SDL_Rect attackingL[1];
		int clipSelect;

		SDL_Surface * optimizeImage(string);
	
};

#endif
