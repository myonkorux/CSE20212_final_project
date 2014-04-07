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
		void display(SDL_Surface *);
		void setX(int);
		void setY(int);
		void setHeight(int);
		void setWidth(int);
		void setMessage(char *);
		void setFontSize(int);
		int getX();
		int getY();
		int getHeight();
		int getWidth();
		char * getMessage();
		int getFontSize();
		void renderBox();
		virtual void update() = 0;
	
	private:
		int height;
		int width;
		int x;
		int y;
		char * message;

		int fontSize;
		SDL_Rect box;
		TTF_Font * font;
		SDL_Color textColor;
		SDL_Surface * messageSurface;
		
};

#endif
