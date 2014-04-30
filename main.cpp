//Christopher Ray, Nathan Vahrenberg
//Professor Scott
//CSE 20212
//29 April 2014

//main.cpp
//Driver program for slayerz

#include"board.h"

int main (int argc, char* args[])
{
	SDL_Init(SDL_INIT_EVERYTHING); 				//initializing SDL
	Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ); 	//initializing SDL audio mixer

	int quit = 0; 						//this variable set to 0 while playing the game, 1 when the user is finished
	Board testBoard; 					//creating the board
	SDL_Event event; 					//will be used to interpret input such as mouse clicks, key presses, etc.
	
	while(quit == 0) 
	{
		if(SDL_PollEvent(&event)) 			//interpretting the event that happened
		{
			if(event.type == SDL_QUIT) 		//loop breaks when the user closes the window that's opened
			{
				quit = 1;
			}
			else
			{	
				testBoard.setEvent(event); 	//events other than closing the window are sent to this function for futher interpretation
			}
		}

		testBoard.update(); 				//updating the board (player/enemy positions, scores, health, etc)
		
		SDL_Delay( 70 ); 				//used to make animations work correctly, but causes slight lag in menus
		
	}	

	testBoard.clean(); 					//closing SDL, TTF, and audio mixer as well as freeing any remaining surfaces and audio clips

	return 0;
}
