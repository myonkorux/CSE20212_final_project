// nvahrenb
// Lab 7-8 progress evidence


#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

class dot{
	public:
		dot();
		void handle_input();
		void move();
		int getx();
		int gety();
	private:
		int x, y;
		int xVel, yVel;
};

dot::dot(){

	x = 100; y = 100;

}

void dot::handle_input(){

	SDL_Event event;

	if( event.type == SDL_KEYDOWN ){
			switch( event.key.keysym.sym ){
				case SDLK_UP:
					yVel -= 10;
					break;
				case SDLK_DOWN:
					yVel += 10;
					break;
				case SDLK_LEFT:
					xVel -= 10;
					break;
				case SDLK_RIGHT:
					xVel += 10;
					break;
			}
		}

}

void dot::move(){

	x += xVel;
	y += yVel;

}

int dot::getx(){

	return x;

}

int dot::gety(){

	return y;

}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination ){
    SDL_Rect offset;
    
    offset.x = x;
    offset.y = y;
    
    SDL_BlitSurface( source, NULL, destination, &offset );
}

int main( int argc, char* args[] ){

	SDL_Surface* dotimg = NULL;
	SDL_Surface* screen = NULL;
	SDL_Event event;
	int quit = 0;
	
	dot dot1;
	
	SDL_Init( SDL_INIT_EVERYTHING );
	
	screen = SDL_SetVideoMode( 640, 480, 32, SDL_SWSURFACE );
	
	dotimg = SDL_LoadBMP( "dot.bmp" );
	
	while( quit == 0 ){
	
		while( SDL_PollEvent( &event ) ){
			dot1.handle_input();
			if( event.type == SDL_QUIT ){
				quit = 1;
			}
		}
	
	dot1.move();
	
	SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );
	
	apply_surface( dot1.getx(), dot1.gety(), dotimg, screen ); 
	
	SDL_Flip( screen );
	
	SDL_Delay ( 1000 );
	
	}
	
	SDL_FreeSurface( dotimg );
	
	SDL_Quit();
	
	return 0;

}
