//Christopher Ray, Nathan Vahrenberg
//Professor Scott
//CSE 20212
//27 March 2014

//Menu.h
//Interface for Menu class, for use with menu

#ifndef MENU_H
#define MENU_H

#include<iostream>
#include<iomanip>
#include<string>
#include"SDL/SDL.h"
#include"SDL/SDL_image.h"
#include"SDL/SDL_ttf.h"

using namespace std;

class Menu
{
	public:
		Menu(); 							//constructor
		int initialize(); 						//function for initializing SDL/SDL_ttf and uploading files and text
		void Clean(); 							//function for freeing images and text as well as closing SDl/SDL_ttf
		void displayMenu(); 						//function for displaying the start menu of our game
	private:
		int loadFiles(); 						//function for loading images and fonts
		void applySurface(int, int, SDL_Surface *, SDL_Surface *); 	//function for applying images or text to the screen
		SDL_Surface * loadImage(string filename); 			//function for loading/optimizing an image for use in loadFiles()

		int screenWidth; 						//screen width
		int screenHeight; 						//screen height
		int screenBPP; 							//screen bits per pixel
		SDL_Surface * screen; 						//the screen
		SDL_Surface * background; 					//the background image that will be used
		SDL_Surface * title; 						//the game title text
		SDL_Surface * start; 						//the start option text
		SDL_Event event; 						//used to keep track of whether or not the user has closed the menu window
		TTF_Font * font; 						//the text font that will be used
		SDL_Color textColor;						//the font color that will be used
};

#endif
