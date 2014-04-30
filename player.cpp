/******************
Chris Ray, Nathan Vahrenberg
Professor Scott
CSE 20212
29 April 2014

player.cpp
Implementation file for Player class, for use with player.h in slayerz
*******************/

#include "player.h"

void Player::apply_PC_sprite( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
	SDL_Rect offset;
	
	offset.x = x; 						//setting the coordinates for the source surface on the destination surface (the screen)
	offset.y = y;
	
	SDL_BlitSurface( source, clip, destination, &offset ); 	//applying the clip of the source surface to the destination surface (the screen)
}

SDL_Surface * Player::optimizeImage(string filename)
{
	SDL_Surface * tempImage = NULL; 					//temporary surface to hold uploaded image
	SDL_Surface * optimized = NULL; 					//surface that will be output

	tempImage = IMG_Load(filename.c_str()); 				//loading the desired image

	if(tempImage != NULL) 							//this is here just in case there is an issue loading the image
	{
		optimized = SDL_DisplayFormat(tempImage); 			//optimized is now the uploaded image
		SDL_FreeSurface(tempImage); 					//freeing tempImage memory

		if( optimized != NULL ) 					//here just in case there was an issue with optimized
		{
		    Uint32 colorkey = SDL_MapRGB( optimized->format, 255, 0, 255 ); //this prevents magenta (color of PC sprite bacground) from being displayed
		    SDL_SetColorKey( optimized, SDL_SRCCOLORKEY, colorkey ); 	//this in effect creates a transparent background for the PC
		}
	}

	return optimized;
}

Player::Player()
{
	//initializing variables
	x = 440;
	y = 300;
	xVel = 0;
	yVel = 0;
	direction = 1;
	health = 666;
	speed = 10;
	power = 10;
	isStanding = 1;
	isAttacking = 0;
	Dead = 0;
	recoil = 0;
	clipSelect = 0;

	//loading audio files	
	attackSound = Mix_LoadWAV("music/waves/mwooshsmallcrit.wav");
	hitSound = Mix_LoadWAV("music/waves/pcHit.wav");
	
	//loading images	
	spritePC = optimizeImage("sprites/ScottPilgrim.bmp");
	spritePCL = optimizeImage("sprites/ScottPilgrimL.bmp");

	int swidth = 43;
	int i;
	
	// Define sprite clippings
	for (i = 0; i <= 7; i++)
	{
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
	}

	for (i = 0; i <= 5; i++)
	{
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
}

int Player::attack(int zombieX, int zombieY)
{
	if ( ((x <= zombieX + 80) && (x + 70 >= zombieX)) && (y <= zombieY + 80) && (y + 70 >= zombieY) && (isAttacking == 1) && enable)
	{
		return power; 	//attempt to apply damage to enemies if they are within range
	}
	else
	{
		return 0;
	}
}

void Player::display( SDL_Surface* source )
{
	int tempX = 0; 			//temporary values for x and y coordinates
	int tempY = 0;

	if (health <= 0)
	{
		Dead = 1; 
		return;
	}
	
	if (direction == 1) 		//checks if player is facing right
	{
		if (isAttacking) 	//applying attacking clip if player is attacking
		{
			Mix_PlayChannel(-1, attackSound, 0);						
			apply_PC_sprite( x, y, spritePC, source, &attacking[ clipSelect ] );
		}
		else if (isStanding) 	//applying attacking clip if player is standing
		{
			apply_PC_sprite( x, y, spritePC, source, &standing[ clipSelect ] );
		}
		else 			//applying moving clip
		{
			apply_PC_sprite( x, y, spritePC, source, &moving[ clipSelect ] );
		}
	}
	else if (direction == -1) 	//checks if player is facing left, same logic above
	{
		if (isAttacking)
		{
			Mix_PlayChannel(-1, attackSound, 0);			
			if (clipSelect == 0 || clipSelect == 2 || clipSelect == 3 || clipSelect == 5)
			{
				apply_PC_sprite( x-20, y, spritePCL, source, &attackingL[ clipSelect ] ); //offset to fix a glitch with left attack animation
			}
			else
			{
				apply_PC_sprite( x, y, spritePCL, source, &attackingL[ clipSelect ] );
			}
		}
		else if (isStanding)
		{
			apply_PC_sprite( x, y, spritePCL, source, &standingL[ clipSelect ] );
		}
		else
		{
			apply_PC_sprite( x, y, spritePCL, source, &movingL[ clipSelect ] );
		}
	}
		
	clipSelect++; 				//increment clip number
	
	if( recoil == 1 || recoil == -1 ) 	//takes care of recoil animation (player knocked back slightly when hit)
	{
		xVel = 0;
		if( clipSelect <= 3 )
		{
			x += recoil*speed/2;
		}
		else if( clipSelect <= 6 && clipSelect >= 4 )
		{ 
			x += (-1)*direction*speed/2;
		}
		else
		{
			recoil = 0;
			clipSelect = 0;
		}
	}
	else if( isAttacking && clipSelect == 6 ) 	//resent clip number if player is still atccking and one attack animation is finished
	{
		isAttacking = 0;
		clipSelect = 0;
	}
	
	tempX = (x + xVel); 				//this chunk of code keeps the player from leaving the screen and the grassy area in the game
	tempY = (y + yVel);
	if((tempX > 0) && (tempX < 840))
	{
		x = tempX;
	}
	if((tempY > 170) && (tempY < 480))
	{
		y = tempY;
	}
	
	if( clipSelect >= 8 ) 				//reset clips once animations have completed a loop
	{
		clipSelect = 0;
	}

}

void Player::update( SDL_Event event )
{
	if(enable) 						//the player will only update if he is not currently paused
	{
		if(!isAttacking) 				//player must finish attacking before any other actions can be done
		{
			if( event.type == SDL_KEYDOWN ) 	//checking for key presses
			{
				switch( event.key.keysym.sym ) 	//allows for WASD or arrow key movement
				{
					case SDLK_RIGHT:
					case SDLK_d:
						isStanding = 0;
						direction = 1;
						xVel = speed;
						break;
					case SDLK_LEFT:
					case SDLK_a:
						isStanding = 0;
						direction = -1;
						xVel = -speed;
						break;
					case SDLK_UP:
					case SDLK_w:
						isStanding = 0;
						yVel = -speed;
						break;
					case SDLK_DOWN:
					case SDLK_s:
						isStanding = 0;
						yVel = speed;
						break;
					case SDLK_SPACE: 	//pressing the space bar causes the player to attack
						isStanding = 1;
						isAttacking = 1;
						xVel = 0;
						clipSelect = 0;
						break;
				}
			}
			else if( event.type == SDL_KEYUP ) 	//checking for key release
			{
				switch( event.key.keysym.sym ) 	//player should default to standing position/animations
				{
					case SDLK_RIGHT:
					case SDLK_LEFT:
					case SDLK_UP:
					case SDLK_DOWN:
					case SDLK_w:
					case SDLK_a:
					case SDLK_s:
					case SDLK_d:
						isStanding = 1;
						xVel = 0;
						yVel = 0;
						break;
					case SDLK_SPACE:
						isStanding = 1;
						isAttacking = 0;
						break;
				}
			}
		}
	}
}

int Player::getX(){

	return x;

}

int Player::getY()
{
	return y;
}

void Player::apply_damage( int damage, int direction )
{
	if(damage > 0) 					//remove player health if damage > 0
	{
		Mix_PlayChannel(-1, hitSound, 0); 	//play sound clip 		
		health -= damage;
		recoil = direction;
		clipSelect = 0;
	}
}

int Player::isDead()
{
	return Dead;
}

void Player::Free_Memory()
{
	Mix_FreeChunk(attackSound);
	Mix_FreeChunk(hitSound);
	SDL_FreeSurface( spritePC );
	SDL_FreeSurface( spritePCL );
}

int Player::getHealth()
{
	return health;
}

void Player::setEnable(int e)
{
	enable = e;
}



