/******************

Chris Ray
Nathan Vahrenberg

University of Notre Dame
CSE20212 - Fundamentals of Computing II
Professor Scott Emrich
Final Project

Spring 2014

*******************/

#include <stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#include "board.h"
#include "player.h"

using namespace std;



int main(){

	// Test item display properties
	
	SDL_Surface* screen = NULL;
	SDL_Event event;
	
	SDL_Init( SDL_INIT_EVERYTHING );
	
	screen = SDL_SetVideoMode( 640, 480, 32, SDL_SWSURFACE );
	
	int quit = 0;
	
	Player P1;
	
	while (quit == 0){
	
		while( SDL_PollEvent( &event ) ){
			//handle_input();
			if( event.type == SDL_QUIT ){
				quit = 1;
			}
		}
		
		SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );
	
		P1.display( screen );
	
		SDL_Flip( screen );
	
		SDL_Delay( 100 );

	}	

	P1.Free_Memory();
	
	SDL_Quit();

}
