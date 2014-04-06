/******************

Chris Ray
Nathan Vahrenberg

box.h

*******************/
#ifndef BOX_H
#define BOX_H

#include <iostream>
#include<iomanip>
#include<string>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

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
		void setMessage(string);
		int getX();
		int getY();
		int getHeight();
		int getWidth();
		void renderBox();
		virtual void update() = 0;
	
	private:
		int height;
		int width;
		int x;
		int y;
		string message;

		SDL_Rect box;
};

#endif