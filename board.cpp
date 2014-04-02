/******************

Chris Ray
Nathan Vahrenberg

board.cpp

*******************/

#include <iostream>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <deque>

#include "board.h"

using namespace std;

// Constructor
Board::Board(){

	// Init values
	start = 1 /* unknown */;
	game = 0 /* unknown */;
	pause = 0;
	over = 0;

}

void Board::display(){



}

void Board::update(SDL_Surface* screen ){

	SDL_Flip( screen );

}

void Board::clean( SDL_Surface* screen ){

	// Fill with white space
	SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );

}
