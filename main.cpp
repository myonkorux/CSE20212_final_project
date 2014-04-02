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

using namespace std;

int main(){

	// Test item display properties
	
	SDL_Surface* dotimg = NULL;
	SDL_Surface* screen = NULL;
	SDL_Event event;
	
	SDL_Init( SDL_INIT_EVERYTHING );
	
	screen = SDL_SetVideoMode( 640, 480, 32, SDL_SWSURFACE );
	
	dotimg = SDL_LoadBMP( "dot.bmp" );
	
	int quit = 0;
	
	Item I1;
	
	while (quit == 0){
	
		while( SDL_PollEvent( &event ) ){
			//handle_input();
			if( event.type == SDL_QUIT ){
				quit = 1;
			}
		}
		
		SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );
	
		I1.display( dotimg, screen );
	
		SDL_Flip( screen );
	
		SDL_Delay( 100 );

	}	

	SDL_FreeSurface( dotimg );
	
	SDL_Quit();

}
