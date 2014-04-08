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
	isStanding = 1;
	
	clipSelect = 0;
	
	spritePC = SDL_LoadBMP("sprites/ScottPilgrim.bmp");
	
	int swidth = 43;
	int mwidth = 50;
	int i;
	
	for (i = 0; i <= 7; i++){
		standing[i].x = swidth*i + 5; 
		standing[i].y = 0;
		standing[i].w = swidth;
		standing[i].h = 68;
	}
	for (i = 0; i <= 7; i++){
		moving[i].x = mwidth*i;
		moving[i].y = 80;
		moving[i].w = mwidth;
		moving[i].h = 66;
	}
}

void Player::display( SDL_Surface* source ){

	if (isStanding){
		apply_PC_sprite( x, y, spritePC, source, &standing[ clipSelect ] );
	}else{
		apply_PC_sprite( x, y, spritePC, source, &moving[ clipSelect ] );
	}
		
	clipSelect++;
	
	if( clipSelect >= 8 ){
		clipSelect = 0;
	}

}

void Player::update(){

	while( SDL_PollEvent( &event ) ){
		if( event.type == SDL_KEYDOWN ){
			switch( event.key.keysym.sym ){
				case SDLK_RIGHT:
					isStanding = 0;
					break;
			}
		}else if( event.type == SDL_KEYUP ){
			switch( event.key.keysym.sym ){
				case SDLK_RIGHT:
					isStanding = 1;
					break;
			}
		}
	}

}

void Player::Free_Memory(){

	SDL_FreeSurface( spritePC );

}
