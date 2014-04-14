/******************

Chris Ray
Nathan Vahrenberg

*******************/

#include <iostream>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

using namespace std;

class Zombie{

	public:
		Zombie();
		void update( int );
		void display( SDL_Surface* );
		void Free_Memory();
	
	
	private:
		int x;
		int y;
		int health;
		int speed;
		int power;
		int xVel;
		int direction;
		int isStanding;
		int isAttacking;
		SDL_Surface* SpriteZombie;
		SDL_Rect moving[3];
		SDL_Rect attacking[3];
		SDL_Rect movingL[3];
		SDL_Rect attackingL[3];
		int clipSelect;
	
};
