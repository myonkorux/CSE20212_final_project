
#include"board.h"

int main (int argc, char* args[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );

<<<<<<< HEAD
=======
Spring 2014

*******************/

/******************


THIS FILE IS NO LONGER IN USE


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
	
	screen = SDL_SetVideoMode( 880, 600, 32, SDL_SWSURFACE );
	
>>>>>>> c51d4d5f45327b7dee2ae61947e6911dc31afad7
	int quit = 0;
	Board testBoard;
	SDL_Event event;
	
	while(quit == 0)
	{
		if(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
			{
				quit = 1;
			}
			else
			{	
				testBoard.setEvent(event);
			}
		}

		testBoard.update();
		
		SDL_Delay( 70 ); // Makes animations work correctly but ruins input and event handling...
		
	}	

	testBoard.clean();

	return 0;
}
