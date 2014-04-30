/******************

Chris Ray
Nathan Vahrenberg

box.h

*******************/
#ifndef BOX_H
#define BOX_H

#include <iostream>
#include<iomanip>
#include<cstring>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include"SDL/SDL_ttf.h"

using namespace std;

class Box
{
	public:
		Box();
		// Function prototypes
		void display(SDL_Surface *);
		void setX(int);
		void setY(int);
		void setHeight(int);
		void setWidth(int);
		void setMessage(string);
		void setFontSize(int);
		void setTextColor(Uint8, Uint8, Uint8);
		void setBoxColor(Uint8, Uint8, Uint8);
		int getX();
		int getY();
		int getHeight();
		int getWidth();
		int getFontSize();
		string getMessage();
		void renderBox();
		void cleanBox();
		virtual int update(SDL_Event) = 0;
	
	private:
		// Properties
		int height;
		int width;
		int x;
		int y;
		string message;

		int fontSize;
		SDL_Rect box;
		TTF_Font * font;
		SDL_Color textColor;
		SDL_Surface * messageSurface;	
		Uint8 boxR;
		Uint8 boxG;
		Uint8 boxB;
			
};

#endif
