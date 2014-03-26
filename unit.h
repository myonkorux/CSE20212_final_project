/******************

Chris Ray
Nathan Vahrenberg

*******************/

#include <iostream>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

using namespace std;

class Unit{

	public:
		Unit();
		void display();
		virtual void update() = 0;
		virtual void move() = 0;
		virtual void attack() = 0;
		virtual void isDead() = 0;	
	
	protected:
		int x;
		int y;
		int health;
		int speed;
		int power;

};
