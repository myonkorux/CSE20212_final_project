/******************

Chris Ray
Nathan Vahrenberg

*******************/

#include <iostream>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#include "player.h"

void apply_PC_sprite( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL ){

	SDL_Rect offset;
	
	offset.x = x;
	offset.y = y;
	
	SDL_BlitSurface( source, clip, destination, &offset );

}

Player::Player(){

	x = 200;
	y = 300;
	health = 100;
	speed = 0;
	power = 0;
	
	clipSelect = 0;
	
	spritePC = SDL_LoadBMP("sprites/ScottPilgrim.bmp");
	
	int width = 43;
	int i;
	
	for (i = 0; i <= 7; i++){
		standing[i].x = width*i + 5; 
		standing[i].y = 0;
		standing[i].w = width;
		standing[i].h = 68;
	}
}

void Player::display( SDL_Surface* source ){

	apply_PC_sprite( x, y, spritePC, source, &standing[ clipSelect ] );

	clipSelect++;
	
	if( clipSelect >= 8 ){
		clipSelect = 0;
	}

}

void Player::update(){



}

void Player::Free_Memory(){

	SDL_FreeSurface( spritePC );

}
