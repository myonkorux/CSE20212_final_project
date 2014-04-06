#include"terrain.h"
#include"Power.h"

int main( int argc, char* args[] )
{
	int screenWidth = 1000;
	int screenHeight = 700;
	int screenBPP = 32;
	
	int quit = 0;

	SDL_Event event;
	SDL_Surface * screen = NULL;
	
	SDL_Init( SDL_INIT_EVERYTHING );
	
	screen = SDL_SetVideoMode( screenWidth, screenHeight, screenBPP, SDL_SWSURFACE );

	Terrain rock(0, 10, 1);
	//Terrain tree(0, 10, 2);
	//Power dot(320, 240, 3);

		
	while (quit == 0){
	
		while( SDL_PollEvent( &event ) ){
			if( event.type == SDL_QUIT ){
				quit = 1;
			}
		}
		
		SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );
	
		rock.display( screen );
		//tree.display(screen);
		//dot.display(screen);
	
		SDL_Flip( screen );
	
		SDL_Delay( 100 );

	}	

	rock.cleanImage();
	//tree.cleanImage();
	//dot.cleanImage();
	
	SDL_Quit();
	
	return 0;
}
