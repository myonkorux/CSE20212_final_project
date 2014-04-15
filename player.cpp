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
	xVel = 0;
	direction = 1;
	health = 100;
	speed = 10;
	power = 0;
	isStanding = 1;
	isAttacking = 0;
	Dead = 0;
	recoil = 0;
	
	clipSelect = 0;
	
	spritePC = SDL_LoadBMP("sprites/ScottPilgrim.bmp");
	spritePCL = SDL_LoadBMP("sprites/ScottPilgrimL.bmp");
	
	int swidth = 43;
	int i;
	
	for (i = 0; i <= 7; i++){
		standing[i].x = swidth*i + 5; 
		standing[i].y = 0;
		standing[i].w = swidth;
		standing[i].h = 68;
		moving[i].y = 80;
		moving[i].h = 66;
		standingL[i].x = 413-(swidth*i + 5)-swidth; 
		standingL[i].y = 0;
		standingL[i].w = swidth;
		standingL[i].h = 68;
		movingL[i].y = moving[i].y;
		movingL[i].h = moving[i].h;
		jumping[i].y = 415;
		jumping[i].h = 486-415;
		jumpingL[i].y = 415;
		jumpingL[i].h = 486-415;
		
	}
	
	for (i = 0; i <= 5; i++){
		attacking[i].y = 145;
		attacking[i].h = 207-145;
		attackingL[i].y = 145;
		attackingL[i].h = 207-145;
	}
	
		moving[0].x = 0;
		moving[0].w = 44-0;
		moving[1].x = 44;
		moving[1].w = 90-44;
		moving[2].x = 90;
		moving[2].w = 147-90;
		moving[3].x = 150;
		moving[3].w = 200-150;
		moving[4].x = 200;
		moving[4].w = 243-200;
		moving[5].x = 243;
		moving[5].w = 290-243;
		moving[6].x = 290;
		moving[6].w = 347-290;
		moving[7].x = 355;
		moving[7].w = 405-355;
		
		movingL[0].x = 413-44;
		movingL[0].w = 44-0;
		movingL[1].x = 413-90;
		movingL[1].w = 90-44;
		movingL[2].x = 413-147;
		movingL[2].w = 147-90;
		movingL[3].x = 413-200;
		movingL[3].w = 200-150;
		movingL[4].x = 413-243;
		movingL[4].w = 243-200;
		movingL[5].x = 413-290;
		movingL[5].w = 290-243;
		movingL[6].x = 413-347;
		movingL[6].w = 347-290;
		movingL[7].x = 413-405;
		movingL[7].w = 405-355;
		
		attacking[0].x = 0;
		attacking[0].w = 63-0;
		attacking[1].x = 63;
		attacking[1].w = 117-63;
		attacking[2].x = 120;
		attacking[2].w = 195-120;
		attacking[3].x = 195;
		attacking[3].w = 265-192;
		attacking[4].x = 267;
		attacking[4].w = 317-267;
		attacking[5].x = 323;
		attacking[5].w = 390-323;
		
		attackingL[0].x = 413-63;
		attackingL[0].w = 63-0;
		attackingL[1].x = 413-117;
		attackingL[1].w = 117-63;
		attackingL[2].x = 413-195;
		attackingL[2].w = 195-120;
		attackingL[3].x = 413-265;
		attackingL[3].w = 265-192;
		attackingL[4].x = 413-317;
		attackingL[4].w = 317-267;
		attackingL[5].x = 413-390;
		attackingL[5].w = 390-323;
		
		jumping[0].x = 0;
		jumping[0].w = 50-0;
		jumping[1].x = 50;
		jumping[1].w = 103-50;
		jumping[2].x = 105;
		jumping[2].w = 152-105;
		jumping[3].x = 162;
		jumping[3].w = 195-162;
		jumping[4].x = 203;
		jumping[4].w = 240-203;
		jumping[5].x = 244;
		jumping[5].w = 276-244;
		jumping[6].x = 280;
		jumping[6].w = 315-280;
		jumping[7].x = 324;
		jumping[7].w = 370-324;
		
		jumpingL[0].x = 413-50;
		jumpingL[0].w = 50-0;
		jumpingL[1].x = 413-103;
		jumpingL[1].w = 103-50;
		jumpingL[2].x = 413-152;
		jumpingL[2].w = 152-105;
		jumpingL[3].x = 413-195;
		jumpingL[3].w = 195-162;
		jumpingL[4].x = 413-240;
		jumpingL[4].w = 240-203;
		jumpingL[5].x = 413-276;
		jumpingL[5].w =	276-244;
		jumpingL[6].x = 413-315;
		jumpingL[6].w = 315-280;
		jumpingL[7].x = 413-370;
		jumpingL[7].w = 370-324;
		
		

}

void Player::display( SDL_Surface* source ){

	if (health <= 0){
		Dead = 1;
	}
	
	if (direction == 1){
		if (isAttacking){
			apply_PC_sprite( x, y, spritePC, source, &attacking[ clipSelect ] );
		}else if (isJumping){
			apply_PC_sprite( x, y, spritePC, source, &jumping[ clipSelect ] );
		}else if (isStanding){
			apply_PC_sprite( x, y, spritePC, source, &standing[ clipSelect ] );
		}else{
			apply_PC_sprite( x, y, spritePC, source, &moving[ clipSelect ] );
		}
	}else if (direction == -1){
		if (isAttacking){
			if (clipSelect == 0 || clipSelect == 2 || clipSelect == 3 || clipSelect == 5){
				apply_PC_sprite( x-20, y, spritePCL, source, &attackingL[ clipSelect ] ); // This block adds an offset to fix a glitch with the left-hand attack animation
			}else{
				apply_PC_sprite( x, y, spritePCL, source, &attackingL[ clipSelect ] );
			}
		}else if (isJumping){
				apply_PC_sprite( x, y, spritePCL, source, &jumpingL[ clipSelect ] );
		}else if (isStanding){
			apply_PC_sprite( x, y, spritePCL, source, &standingL[ clipSelect ] );
		}else{
			apply_PC_sprite( x, y, spritePCL, source, &movingL[ clipSelect ] );
		}
	}
		
	clipSelect++;
	
	if( recoil ){
		xVel = 0;
		if( clipSelect <= 3 ){
			y -= 5*( 3-clipSelect );
			x += (-1)*direction*speed/2;
		}else if( clipSelect <= 6 && clipSelect >= 4 ){ 
			y += 5*( 3-(clipSelect-3) );
			x += (-1)*direction*speed/2;
		}else{
			recoil = 0;
			clipSelect = 0;
		}
	}else if( isAttacking && clipSelect == 6 ){
		isAttacking = 0;
		clipSelect = 0;
	}else if( isJumping ){
		if( clipSelect <= 3 ){
			y -= 10*( 3-clipSelect );
		}else if( clipSelect <= 6 && clipSelect >= 4 ){ 
			y += 10*( 3-(clipSelect-3) );
		}else{
			isJumping = 0;
			clipSelect = 0;
		}
	}
	
	x += xVel;
	
	if( clipSelect >= 8 ){
		clipSelect = 0;
	}

}

void Player::update( SDL_Event event ){

	if(!isAttacking){
		if( event.type == SDL_KEYDOWN ){
			switch( event.key.keysym.sym ){
				case SDLK_RIGHT:
					isStanding = 0;
					direction = 1;
					xVel = speed;
					break;
				case SDLK_LEFT:
					isStanding = 0;
					direction = -1;
					xVel = -speed;
					break;
				case SDLK_SPACE:
					isStanding = 1;
					isAttacking = 1;
					xVel = 0;
					clipSelect = 0;
					break;
				case SDLK_UP:
					isJumping = 1;
					clipSelect = 0;
					break;
			}
		}else if( event.type == SDL_KEYUP ){
			switch( event.key.keysym.sym ){
				case SDLK_RIGHT:
				case SDLK_LEFT:
					isStanding = 1;
					xVel = 0;
					break;
				case SDLK_SPACE:
					break;
		
			}
		}
	}

}

int Player::getX(){

	return x;

}

void Player::apply_damage( int damage ){

	if(damage > 0){
		health -= damage;
		recoil = 1;
		clipSelect = 0;
	}

}

int Player::isDead(){

	return Dead;

}

void Player::Free_Memory(){

	SDL_FreeSurface( spritePC );
	SDL_FreeSurface( spritePCL );

}
