/******************

Chris Ray
Nathan Vahrenberg

*******************/

#ifndef FRANKENSTEIN_H
#define FRANKENSTEIN_H

#include <iostream>
#include<iomanip>
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
		int getPoints();
		void setEnable(int);
	
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
		int dying;
		int Dead;
		int points;
		int enable;
		SDL_Surface* SpriteFrankenstein;
		SDL_Rect moving[3];
		SDL_Rect attacking[3];
		SDL_Rect movingL[3];
		SDL_Rect attackingL[3];
		SDL_Rect dying[10];
		int clipSelect;

		SDL_Surface * optimizeImage(string);
	
};

#endif
