//Christopher Ray, Nathan Vahrenberg
//Professor Scott
//CSE 20212
//27 March 2014

//Menu.cpp
//Implementation for Menu class, for use with menu

#include"Menu.h"

Menu::Menu()
{
	screenWidth = 640; 	//initializing private data members
	screenHeight = 480;
	screenBPP = 32;
	screen = NULL; 		//the surfaces and text will be redefined in other functions
	background = NULL;
	title = NULL;
	start = NULL;
	font = NULL;
	textColor = {0, 0, 0}; 	//font color will be black
}

int Menu::initialize()
{
	if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
	{
		return 0; 							//end the program if SDL does not initialize
	}

	if( TTF_Init() == -1 )
	{
		return 0; 							//end the program if SDL_ttf does not initialize
	}

	screen = SDL_SetVideoMode(screenWidth, screenHeight, screenBPP, SDL_SWSURFACE);
	if( screen == NULL )
	{
		return 0; 							//end the program if the screen is not properly created
	}
	SDL_WM_SetCaption( "Start Screen Test", NULL ); 			//setting the screen's caption

	if(loadFiles() == 0)
	{
		return 0; 							//end the program if the files and font are not properly loaded
	}
	title = TTF_RenderText_Solid(font, "Zombie Slayerz", textColor); 	//creating the text objects
	start = TTF_RenderText_Solid(font, "Start", textColor);

	return 1;
}

void Menu::Clean()
{
	SDL_FreeSurface(background); 	//freeing the image and text
	SDL_FreeSurface(title);
	SDL_FreeSurface(start);
	TTF_CloseFont(font); 
	
	TTF_Quit(); 			//quitting SDL_ttf and SDL
	SDL_Quit();
}

SDL_Surface * Menu::loadImage(string filename)
{
	SDL_Surface* loadedImage = NULL; 		//temporary storage for uploaded image

	SDL_Surface* optimizedImage = NULL; 		//where the image will be stored once it has been optimized

	loadedImage = IMG_Load( filename.c_str() ); 	//loading the image

	if( loadedImage != NULL ) 			//optimize the loaded image for the screen, assuming it loaded properly
	{
		optimizedImage = SDL_DisplayFormat( loadedImage );
		SDL_FreeSurface( loadedImage );

		if( optimizedImage != NULL )
		{
		    Uint32 colorkey = SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF );
		    SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, colorkey );
		}
	}

	return optimizedImage; 
}

int Menu::loadFiles()
{
	background = loadImage("gloomy_bg1.bmp");
	if( background == NULL )
	{
		return 0; 	//return 0 if the background image fails to load properly
	}

	font = TTF_OpenFont( "lazy.ttf", 60 );
	if( font == NULL )
	{
		return 0; 	//return 0 if the font fails to load properly
	}

	return 1;
}

void Menu::applySurface(int x, int y, SDL_Surface * source, SDL_Surface * destination)
{
	SDL_Rect offset; 					//creating offset for use with SDL_BlitSurface
	offset.x = x;
	offset.y = y;

	SDL_BlitSurface( source, NULL, destination, &offset ); 	//the function that actually sends the image to the screen
}

void Menu::displayMenu()
{
	int quit = 0;

	applySurface(0, 0, background, screen); 								//setting the background
	applySurface( ( screenWidth - title->w ) / 2, ( screenHeight - title->h ) / 4, title, screen ); 	//setting the title text
	applySurface((screenWidth - start->w) / 2,(screenHeight - start->h) / 2, start, screen); 		//setting the start option text

	if( SDL_Flip( screen ) == -1 )
	{
		return; 									//end the program if the screen is not properly updated
	}

	while(quit == 0) 
	{
		while(SDL_PollEvent(&event)) 
		{
			if(event.type == SDL_QUIT) 						//if the user closes the window, quit = 1 and the function ends
			{
				quit = 1;
			}
		}
	}
}





