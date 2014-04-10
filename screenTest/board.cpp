/******************

Chris Ray
Nathan Vahrenberg

board.cpp

*******************/

#include "board.h"

using namespace std;

// Constructor
Board::Board()
{
	// Init values
	start = 1 /* unknown */;
	select = 0;
	game = 0 /* unknown */;
	pause = 0;
	over = 0;

	screenWidth = 880;
	screenHeight = 600;
	screenBPP = 32;

	screen = NULL;
	background = NULL;
}

void Board::initialize()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	screen = SDL_SetVideoMode(screenWidth, screenHeight, screenBPP, SDL_SWSURFACE);
	TTF_Init();
	SDL_WM_SetCaption( "Zombie Slayerz", NULL );
}

SDL_Surface * Board::optimizeImage(string filename)
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

void Board::loadBackground()
{
	background = optimizeImage("forest.jpg");
}

void Board::clearDeques()
{
	deque<Text>::const_iterator i;
	for(i = textBoxes.begin(); i != textBoxes.end(); ++i)
	{
		*i.cleanBox();
	}	
	textBoxes.clear();

	deque<Button>::const_iterator j;
	for(j = buttons.begin(); j != buttons.end(); ++j)
	{
		*j.cleanBox();
	}	
	buttons.clear();

	deque<Counter>::const_iterator k;
	for(k = counters.begin(); k != counters.end(); ++k)
	{
		*k.cleanBox();
	}	
	counters.clear();
}

void Board::startState()
{	
	clearDeques();
	
	Text titleCard(720, 120, 80, 40, 110, "Zombie Slayerz");
	Text developers(720, 40, 80, 200, 30, "Developed by cray & nvahrenb");
	Text cseLabel(160, 40, 40, 720, 30, "CSE 20212");
	Text versionLabel(160, 40, 680, 720, 30, "Pre-Alpha");
	texBoxes.push_back(titleCard);
	texBoxes.push_back(developers);
	texBoxes.push_back(cseLabel);
	texBoxes.push_back(versionLabel);
	

	Button startButton(240, 80, 320, 280, 70, "Start");
	Button quitButton(240, 80, 320, 400, 70, "Quit");
	buttons.push_back(startButton);
	buttons.push_back(quitButton);
}

void Board::selectState()
{
	clearDeques();
	
	Button titleCard(720, 120, 80, 40, 110, "Select Difficulty");
	Button easyButton(240, 80, 320, 200, 70, "Easy");
	Button normalButton(240, 80, 320, 320, 70, "Normal");
	Button hardButton(240, 80, 320, 440, 70, "Hard");
	buttons.push_back(titleCard);
	buttons.push_back(easyButton);
	buttons.push_back(normalButton);
	buttons.push_back(hardButton);

	Text cseLabel(160, 40, 40, 720, 30, "CSE 20212");
	Text versionLabel(160, 40, 680, 720, 30, "Pre-Alpha");
	texBoxes.push_back(cseLabel);
	texBoxes.push_back(versionLabel);	
}

void Board::display()
{

}

void Board::update(SDL_Surface* screen )
{
	SDL_Flip( screen );
}

void Board::wipe( SDL_Surface* screen )
{
	// Fill with white space
	SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );
}
