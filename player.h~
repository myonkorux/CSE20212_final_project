/******************

Chris Ray, Nathan Vahrenberg
Professor Scott
CSE 20212
29 April 2014

player.h
Header file for Player class, for use with player.cpp in slayerz

*******************/

#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include<iomanip>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"

using namespace std;

class Player
{
	public:
		Player(); 			//constructor
		void display( SDL_Surface* ); 	//function for displaying player on screen (handles animations specifically)
		void update( SDL_Event ); 	//function for updating position, stats, and status depending on SDL event
		int attack(int, int); 		//function for attacking (specifically outputting damage amount)
		void apply_damage( int, int ); 	//function for taking damage
		int isDead(); 			//returns 1 if the player is dead, 0 if he's still fighting
		void Free_Memory(); 		//function for freeing player image and audio
		int getX(); 			//returns player's x coordinate
		int getY(); 			//returns player's y coordinate
		int getHealth(); 		//returns the player's health
		void setEnable(int); 		//used to set the value of enable (used for pausing the game)
		
	private:
		int x; 		//player's x coordinate
		int y; 		//player's y coordinate
		int xVel; 	//player's x velocity
		int yVel; 	//player's y velocity
		int direction; 	//direction player is facing
		int health; 	//player's health
		int speed; 	//player's speed
		int enable; 	//if 1, player can move, attack, be damaged, etc; if 0, player is effectively suspended or paused
		int power; 	//player's attack power

		SDL_Surface * spritePC; 	//the player character image (right-facing)
		SDL_Surface * spritePCL; 	//the player character image (left-facing)
		SDL_Rect standing[8]; 		//clips for the standing animation (right)
		SDL_Rect moving[8]; 		//clips for the moving animation (right)
		SDL_Rect attacking[6]; 		//clips for the attacking animation (right)
		SDL_Rect standingL[8]; 		//clips for the standing animation (left)
		SDL_Rect movingL[8]; 		//clips for the moving animation (left)
		SDL_Rect attackingL[6]; 	//clips for the attacking animation (left)

		Mix_Chunk * attackSound; 	//attack sound clip
		Mix_Chunk * hitSound; 		//sound clip for taking damage

		int clipSelect; 		//used to increment throught the clip arrays
		int isStanding; 		//returns 1 if the player is standing
		int isAttacking; 		//returns 1 if the player is attacking
		int Dead; 			//1 if dead, 0 if alive
		int recoil; 			//value of player recoil (used when taking damage)

		SDL_Surface * optimizeImage(string); 						//function for optimizing an uploaded image

		void apply_PC_sprite(int, int, SDL_Surface *, SDL_Surface *, SDL_Rect *); 	//function for displaying PC image on screen 

};

#endif
