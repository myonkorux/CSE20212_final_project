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
		void update();
		void move();
		void attack();
		void isDead();
		void Free_Memory();
		
	private:
		int x;
		int y;
		int health;
		int speed;
		int power;
		SDL_Surface* spritePC;
		SDL_Rect standing[8];
		int clipSelect;

};
