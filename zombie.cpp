//Christopher Ray, Nathan Vahrenberg
//Professor Scott
//CSE 20212
//29 April 2014

//zombie.cpp
//Implementation for Zombie class, for use with zombie.h in slayerz

#include "zombie.h"

void Zombie::apply_zombie_sprite( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
	SDL_Rect offset;
	
	offset.x = x; 						//setting the coordinates for the source surface on the destination surface (the screen)
	offset.y = y;
	
	SDL_BlitSurface( source, clip, destination, &offset ); 	//applying the clip of the source surface to the destination surface (the screen)
}

SDL_Surface * Zombie::optimizeImage(string filename)
{
	SDL_Surface * tempImage = NULL; 			//temporary surface to hold uploaded image
	SDL_Surface * optimized = NULL; 			//surface that will be output

	tempImage = IMG_Load(filename.c_str()); 		//loading the desired image

	if(tempImage != NULL) 					//this is here just in case there is an issue loading the image
	{
		optimized = SDL_DisplayFormat(tempImage); 	//optimized is now the uploaded image
		SDL_FreeSurface(tempImage); 			//freeing tempImage memory

		if( optimized != NULL ) 			//here just in case there was an issue with optimized
		{
		    Uint32 colorkey = SDL_MapRGB( optimized->format, 8, 112, 80 ); //this prevents magenta (color of PC sprite bacground) from being displayed
		    SDL_SetColorKey( optimized, SDL_SRCCOLORKEY, colorkey ); 	//this in effect creates a transparent background for the PC
		}
	}

	return optimized;
}

Zombie::Zombie(){

	// Initialize variables
	x = rand()%800+40; //zombies spawn at random x coord, but same y coord
	if((x > 300) && (x < 600))
	{
		x = 100;
	}
	y = 318;
	xVel = 0;
	yVel = 0;
	direction = 1;
	health = 30;
	speed = 1;
	power = 10;
	isStanding = 1;
	isAttacking = 0;
	isDying = 0;
	Dead = 0;
	points = 10;
	enable = 0;
	handicap = 0;

	spawn = Mix_LoadWAV("music/waves/zombieSpawn.wav"); //loading spawn sound clip
	die = Mix_LoadWAV("music/waves/zombieDeath.wav"); //loading death sound clip
	Mix_PlayChannel(-1, spawn, 0);
	
	clipSelect = 0;
	
	SpriteZombie = optimizeImage("sprites/zombie.bmp"); //loading image
	
	// Define sprite clips
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
	
	dying[0].x = 5;
	dying[0].w = 25-5;
	dying[1].x = 30;
	dying[1].w = 70-30;
	dying[2].x = 70;
	dying[2].w = 110-70;
	dying[3].x = 115;
	dying[3].w = 155-115;
	dying[4].x = 155;
	dying[4].w = 195-155;
	dying[5].x = 195;
	dying[5].w = 235-195;
	dying[6].x = 235;
	dying[6].w = 275-235;
	dying[7].x = 5;
	dying[7].w = 45-5;
	dying[8].x = 45;
	dying[8].w = 75-45;
	dying[9].x = 75;
	dying[9].w = 105-75;
	
	dying[0].y = 285;
	dying[0].h = 335-285;
	dying[1].y = 285;
	dying[1].h = 335-285;
	dying[2].y = 285;
	dying[2].h = 335-285;
	dying[3].y = 285;
	dying[3].h = 335-285;
	dying[4].y = 285;
	dying[4].h = 335-285;
	dying[5].y = 285;
	dying[5].h = 335-285;
	dying[6].y = 285;
	dying[6].h = 335-285;
	dying[7].y = 335;
	dying[7].h = 385-335;
	dying[8].y = 335;
	dying[8].h = 385-335;
	dying[9].y = 335;
	dying[9].h = 385-335;

}

void Zombie::display( SDL_Surface* source )
{	
	int tempX = 0;				 //temporary values for x and y coordinates
	int tempY = 0;

	if(health <= 0 && isDying == 0)
	{
		Mix_PlayChannel(-1, die, 0); 	//play death sound clip if zombie dies		
		isDying = 1;
		clipSelect = 0;
	}

	tempX = (x + xVel); 			//zombies will always move towards player location 
	tempY = (y + yVel);
	if((tempX > 0) && (tempX < 840) && !(isDying))
	{
		x = tempX;
	}
	if((tempY > 0) && (tempY < 540) && !(isDying))
	{
		y = tempY;
	}

	if( clipSelect >= 3 && !isDying) 	//reset clips for walk cycle
	{
		clipSelect = 0;
	}
	
	if( isDying && clipSelect >= 10 ) 	//reset clips once death animation completes
	{
		Dead = 1;
		isDying = 0;
		return;
	}
	
	// Select sprite to display
	if (isDying) 				//death animation
	{
		apply_zombie_sprite( x, y, SpriteZombie, source, &dying[ clipSelect ]);
	}
	else if (direction == 1) 		//walking to the right
	{
		apply_zombie_sprite( x, y, SpriteZombie, source, &moving[ clipSelect ]);
	}
	else 					//walking to the left
	{
		apply_zombie_sprite( x, y, SpriteZombie, source, &movingL[ clipSelect ]);
	}

	clipSelect++;

}

void Zombie::update( int playerX, int playerY )
{
	if(enable) 			//zombies will only update if the game is not paused or in the menus
	{		
		switch(handicap) 	//changing stat based on powerup collected
		{
			case 1: 	//mic
			health = 0;
			break;

			case 2: 	//guitar
			speed = (speed / 2);
			break;

			case 3: 	//bass
			power = (power / 2);
			break;

			case 4: 	//drum
			speed = 0;
			break;
		}
		
		//change zombie x coord so that it move closer to the player's x coord
		if( playerX < x )
		{
			direction = -1;
			if( x <= playerX + 45 )
			{
				xVel = 0;
			}
			else
			{
				xVel = direction * speed;
			}
		}
		else
		{
			direction = 1;
			if( x + 30 >= playerX  )
			{
				xVel = 0;
			}
			else
			{
				xVel = direction * speed;
			}
		}

		//change zombie y coord so that it move closer to the player's x coord
		if( playerY < y )
		{
			yVel = -speed;
		}
		else if( playerY > y)
		{
			yVel = speed;
		}
		else
		{
			yVel = 0;
		}
	}
}

int Zombie::attack( int playerX, int playerY )
{

	if ( (x <= playerX + 50) && (x + 35 >= playerX) && (playerY <= y + 35) && (playerY + 50 >= y) && enable)
	{
		return power; 	//apply damage to the player if in range
	}
	else
	{
		return 0;
	}

}

void Zombie::Free_Memory()
{
	Mix_FreeChunk(spawn);
	Mix_FreeChunk(die);
	SDL_FreeSurface( SpriteZombie );
}

void Zombie::applyDamage(int damage)
{
	if(damage > 0)
	{
		health -= damage; //subtract damage from health
	}
}

// Get functions
int Zombie::getX()
{
	return x;
}

int Zombie::getY()
{
	return y;
}

int Zombie::getDirection()
{
	return direction;
}

int Zombie::isDead()
{	
	return Dead;
}

int Zombie::getPoints()
{
	return points;
}

// Set functions
void Zombie::setEnable(int e)
{
	enable = e;
}

void Zombie::setHandicap(int newh)
{
	handicap = newh;
}
