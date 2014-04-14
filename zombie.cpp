/******************

Chris Ray
Nathan Vahrenberg

*******************/

#include <iostream>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#include "zombie.h"

void apply_zombie_sprite( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL ){

	SDL_Rect offset;
	
	offset.x = x;
	offset.y = y;
	
	SDL_BlitSurface( source, clip, destination, &offset );

}

Zombie::Zombie(){

	x = 400;
	y = 318;
	xVel = 0;
	direction = 1;
	health = 100;
	speed = 2;
	power = 0;
	isStanding = 1;
	isAttacking = 0;
	
	clipSelect = 0;
	
	SpriteZombie = SDL_LoadBMP("sprites/zombie.bmp");
	
	moving[0].y = 140;
	moving[0].h = 50;
	movingL[0].y = 140;
	movingL[0].h = 50;
	moving[1].y = 140;
	moving[1].h = 50;
	movingL[1].y = 140;
	movingL[1].h = 50;
	moving[2].y = 140;
	moving[2].h = 50;
	movingL[2].y = 140;
	movingL[2].h = 50;
	
	movingL[0].x = 8;
	movingL[0].w = 30;
	movingL[1].x = 40;
	movingL[1].w = 30;
	movingL[2].x = 78;
	movingL[2].w = 30;
	
	moving[0].x = 118;
	moving[0].w = 30;
	moving[1].x = 158;
	moving[1].w = 30;
	moving[2].x = 195;
	moving[2].w = 30;

}

void Zombie::display( SDL_Surface* source ){

	x += xVel;

	if( clipSelect >= 3 ){
		clipSelect = 0;
	}
	
	if (direction == 1){
		apply_zombie_sprite( x, y, SpriteZombie, source, &moving[ clipSelect ]);
	}else{
		apply_zombie_sprite( x, y, SpriteZombie, source, &movingL[ clipSelect ]);
	}

	clipSelect++;

}

void Zombie::update( int playerX ){

	

	if( playerX < x ){
		direction = -1;
		if( x <= playerX + 45  ){
			xVel = 0;
		}else{
			xVel = direction * speed;
		}
	}else{
		direction = 1;
		if( x + 30 >= playerX  ){
			xVel = 0;
		}else{
			xVel = direction * speed;
		}
	}
	
	

}

void Zombie::Free_Memory(){

	SDL_FreeSurface( SpriteZombie );

}
