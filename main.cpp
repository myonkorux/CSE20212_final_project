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
#include "zombie.h"

using namespace std;



int main(){
	
	int damage;
	
	SDL_Surface* screen = NULL;
	SDL_Event event;
	
	SDL_Init( SDL_INIT_EVERYTHING );
	
	screen = SDL_SetVideoMode( 640, 480, 32, SDL_SWSURFACE );
	
	int quit = 0;
	
	Player P1;
	Zombie Z1;
	
	while (quit == 0){
		
		damage = 0;
		
		if( SDL_PollEvent( &event ) ){
			if( event.type == SDL_QUIT ){
				quit = 1;
			}else{
				P1.update( event );
			}
		}
		
		SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );
	
		Z1.display( screen );
		P1.display( screen );
		
		Z1.update( P1.getX() );
		damage += Z1.attack( P1.getX() );
		
		P1.apply_damage( damage );
	
		SDL_Flip( screen );
	
		SDL_Delay( 100 );

	}	

	P1.Free_Memory();
	Z1.Free_Memory();
	
	SDL_Quit();

}
