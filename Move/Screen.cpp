//Christopher Ray
//Professor Scott
//CSE 20212

//Screen.cpp
//Implementation for class Screen, for use in Move

#include"Screen.h"

Screen::Screen()
{
	screenH = 480;
	screenW = 640;
	screenBPP = 32;
	
	screen = NULL;
	figure = NULL;
}

int Screen::initialize()
{
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		cout << "SDL failed to initialize." << endl;		
		return 0;
	}
	
	screen = SDL_SetVideoMode(screenW, screenH, screenBPP, SDL_SWSURFACE);
	SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF ));
	if(screen == NULL)
	{
		cout << "Screen failed to load." << endl;				
		return 0;
	}

	figure = loadImage("foo.png");
	if(figure == NULL)
	{
		cout << "Figure failed to load." << endl;
		return 0;
	}

	SDL_WM_SetCaption( "Animation Test", NULL );
}

void Screen::cleanUp()
{
	SDL_FreeSurface(figure);
	SDL_Quit();
}

SDL_Surface * Screen::loadImage(string filename)
{
	SDL_Surface * tempImage = NULL;
	SDL_Surface * optimized = NULL;

	tempImage = IMG_Load(filename.c_str());

	if(tempImage != NULL)
	{
		optimized = SDL_DisplayFormat(tempImage);
		SDL_FreeSurface(tempImage);

		if( optimized != NULL )
		{
		    Uint32 colorkey = SDL_MapRGB( optimized->format, 0, 0xFF, 0xFF );
		    SDL_SetColorKey( optimized, SDL_SRCCOLORKEY, colorkey );
		}
	}

	return optimized;
}

void Screen::applySurface(int x, int y, SDL_Surface * source, SDL_Surface * destination)
{
	SDL_Rect offset;
	
	offset.x = x;
	offset.y = y;

	SDL_BlitSurface( source, NULL, destination, &offset );
}

void Screen::animate()
{
	int quit = 0;
	SDL_Event event;

	applySurface(320, 240, figure, screen);

	while(quit == 0)
	{
		while( SDL_PollEvent( &event ) )
		{
			if( event.type == SDL_QUIT )
			{
				quit = 1;
			}
		}

		Uint8 * keystates = SDL_GetKeyState( NULL );

		if( keystates[ SDLK_UP ] )
		{
			SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );			
			applySurface(320, 140, figure, screen);
		}

		if( keystates[ SDLK_DOWN ] )
		{
			SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );			
			applySurface(320, 340, figure, screen);
		}

		if( keystates[ SDLK_LEFT ] )
		{
			SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );			
			applySurface(220, 240, figure, screen);
		}

		if( keystates[ SDLK_RIGHT ] )
		{
			SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );			
			applySurface(420, 240, figure, screen);
		}

		if( SDL_Flip( screen ) == -1 )
		{
			return;
		}

		SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );
		applySurface(320, 240, figure, screen);
	}
}

