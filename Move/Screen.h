//Christopher Ray
//Professor Scott
//CSE 20212

//Screen.h
//Interface for class Screen, for use in Move

#ifndef SCREEN_H
#define SCREEN_H

#include<iostream>
#include<iomanip>
#include<string>
#include"SDL/SDL.h"
#include"SDL/SDL_image.h"

using namespace std;

class Screen
{
	public:
		Screen();
		int initialize();
		void animate();
		void cleanUp();
		
	private:
		void applySurface(int, int, SDL_Surface *, SDL_Surface *);
		int screenH;
		int screenW;
		int screenBPP;
		SDL_Surface * loadImage(string);
		SDL_Surface * screen;
		SDL_Surface * figure;
};

#endif
