#include"board.h"

int main (int argc, char* args[])
{
	SDL_Init(SDL_INIT_EVERYTHING);

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
		
		SDL_Delay( 100 ); // Makes animations work correctly but ruins input and event handling...
		
	}	

	testBoard.clean();

	return 0;
} 
