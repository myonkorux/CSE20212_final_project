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
				testBoard.update(event);
			}
		}
	}	

	testBoard.clean();

	return 0;
} 
