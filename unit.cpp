/******************

Chris Ray
Nathan Vahrenberg

*******************/

#include <iostream>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#include "unit.h"

using namespace std;

// Constructor
Unit::Unit(){

	x = 400;
	y = 300;
	xVel = 0;
	direction = 1;
	health = 100;
	speed = 10;
	power = 0;
	isStanding = 1;
	isAttacking = 0;

}
