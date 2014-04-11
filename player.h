/******************

Chris Ray
Nathan Vahrenberg

*******************/

#include <iostream>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

using namespace std;

using namespace std;

class Player{

	public:
		Player();
		void display( SDL_Surface* );
		void update( SDL_Event );
		void move();
		void attack();
		void isDead();
		void Free_Memory();
		
	private:
		int x;
		int y;
		int xVel;
		int direction;
		int health;
		int speed;
		int power;
		SDL_Surface* spritePC;
		SDL_Surface* spritePCL;
		SDL_Rect standing[8];
		SDL_Rect moving[8];
		SDL_Rect attacking[6];
		SDL_Rect standingL[8];
		SDL_Rect movingL[8];
		SDL_Rect attackingL[6];
		SDL_Event event;
		int clipSelect;
		int isStanding;
		int isAttacking;

};
