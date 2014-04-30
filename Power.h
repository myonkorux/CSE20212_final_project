//Christopher Ray, Nathan Vahrenberg
//Professor Scott
//CSE 20212
//29 April 2014

//Power.h
//Implmentation for Power class, for use with Power.cpp in slayerz

#ifndef POWER_H
#define POWER_H

#include"item.h"

class Power : public Item 				//Power class inherits from Item class
{
	public:
		Power(int, int ,int); 			//constructor
		void display(SDL_Surface *); 		//function for displaying powerup on screen
		void cleanImage(); 			//function for freeing memory or powerup image
	private:
		SDL_Surface * PowerImage; 		//the image for the powerup
		float yOffset; 				//used for floating animation
		float t; 				//used for floating animation
		SDL_Rect clip; 				//used to clip the powerup image
		void chooseImage(); 			//function for determining which clip to use
		
		SDL_Surface * optimizeImage(string); 	//function for optimizing an uploaded image (creating transparent background)
			
};

#endif
