/******************

Chris Ray
Nathan Vahrenberg

*******************/

#include <iostream>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#include "axebaby.h"

// Function to send sprite to screen
void apply_axebaby_sprite( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL ){

	SDL_Rect offset;
	
	offset.x = x;
	offset.y = y;
	
	SDL_BlitSurface( source, clip, destination, &offset );

}

// Optimize function to set a transparent background
SDL_Surface * Axebaby::optimizeImage(string filename)
{
	SDL_Surface * tempImage = NULL;
	SDL_Surface * optimized = NULL;

	tempImage = IMG_Load(filename.c_str());

	if(tempImage != NULL)
	{
		optimized = SDL_DisplayFormat(tempImage);
		SDL_FreeSurface(tempImage);

		if( optimized != NULL )
		{
		    Uint32 colorkey = SDL_MapRGB( optimized->format, 64, 64, 64 );
		    SDL_SetColorKey( optimized, SDL_SRCCOLORKEY, colorkey );
		}
	}

	return optimized;
}

// Constructor
Axebaby::Axebaby(){

	// Initialize variables
	x = rand()%800+40;
	if((x > 300) && (x < 600))
	{
		x = 100;
	}
	y = 318;
	xVel = 0;
	yVel = 0;
	direction = 1;
	health = 10;
	speed = 4;
	power = 5;
	isStanding = 1;
	isAttacking = 0;
	Dead = 0;
	points = 20;
	enable = 0;
	handicap = 0;
	isDying = 0;
	
	clipSelect = 0;
	
	// Load external resources
	SpriteAxebaby = optimizeImage("sprites/axebaby.bmp");
	spawn = Mix_LoadWAV("music/waves/babySpawn.wav");
	die = Mix_LoadWAV("music/waves/babyDeath.wav");
	Mix_PlayChannel(-1, spawn, 0);
	
	int i;
	
	// Define sprite clippings
	for( i = 0; i <= 3; i++ ){
		moving[i].y = 117;
		moving[i].h = 147-117;
		movingL[i].y = 80;
		movingL[i].h = 110-80;
	}

	moving[0].x = 10;
	moving[0].w = 25-10;
	moving[1].x = 32;
	moving[1].w = 47-32;
	moving[2].x = 55;
	moving[2].w = 70-55;
	moving[3].x = 77;
	moving[3].w = 92-77;

	movingL[0].x = 10;
	movingL[0].w = 25-10;
	movingL[1].x = 32;
	movingL[1].w = 47-32;
	movingL[2].x = 55;
	movingL[2].w = 70-55;
	movingL[3].x = 77;
	movingL[3].w = 92-77;
	
	attacking[0].x = 55;
	attacking[0].w = 82-55;
	attacking[0].y = 172;
	attacking[0].h = 198-172;
	
	attackingL[0].x = 4;
	attackingL[0].w = 31-4;
	attackingL[0].y = 172;
	attackingL[0].h = 198-172;
	
	dying[0].x = 10;
	dying[0].w = 35-10;
	dying[1].x = 35;
	dying[1].w = 60-35;
	dying[2].x = 60;
	dying[2].w = 90-60;
	dying[3].x = 15;
	dying[3].w = 45-15;
	dying[4].x = 50;
	dying[4].w = 90-50;
	dying[5].x = 15;
	dying[5].w = 50-15;
	dying[6].x = 55;
	dying[6].w = 80-55;
	dying[7].x = 25;
	dying[7].w = 45-25;
	dying[8].x = 50;
	dying[8].w = 70-50;
	
	dying[0].y = 225;
	dying[0].h = 260-225;
	dying[1].y = 225;
	dying[1].h = 260-225;
	dying[2].y = 225;
	dying[2].h = 260-225;
	dying[3].y = 260;
	dying[3].h = 300-260;
	dying[4].y = 260;
	dying[4].h = 300-260;
	dying[5].y = 305;
	dying[5].h = 335-305;
	dying[6].y = 305;
	dying[6].h = 335-305;
	dying[7].y = 335;
	dying[7].h = 355-335;
	dying[8].y = 335;
	dying[8].h = 355-335;

}

// Display function
void Axebaby::display( SDL_Surface* source )
{	
	int tempX = 0;
	int tempY = 0;

	if((health <= 0) && (isDying == 0))
	{
		Mix_PlayChannel(-1, die, 0);		
		isDying = 1;
		clipSelect = 0;
	}

	// Check validity of location and update
	tempX = (x + xVel);
	tempY = (y + yVel);
	if((tempX > 0) && (tempX < 840) && !isDying)
	{
		x = tempX;
	}
	if((tempY > 0) && (tempY < 540) && !isDying)
	{
		y = tempY;
	}
	
	if( clipSelect >= 4 && !isDying)
	{
		clipSelect = 0;
	}
	
	if( clipSelect >= 10 && isDying )
	{
		Dead = 1;
		isDying = 0;
		return;
	}
	
	// Select correct sprite clip to apply
	if( isDying )
	{
		apply_axebaby_sprite( x, y, SpriteAxebaby, source, &dying[ clipSelect ]);
	}
	else if (direction == 1)
	{
		if(isAttacking)
		{
			apply_axebaby_sprite( x, y, SpriteAxebaby, source, &attacking[ 0 ]);
		}
		else
		{
			apply_axebaby_sprite( x, y, SpriteAxebaby, source, &moving[ clipSelect ]);
		}
	}
	else
	{
		if(isAttacking)
		{
			apply_axebaby_sprite( x, y, SpriteAxebaby, source, &attackingL[ 0 ]);
		}
		else
		{
			apply_axebaby_sprite( x, y, SpriteAxebaby, source, &movingL[ clipSelect ]);
		}
	}
	clipSelect++;
}

// Update function handles all changes to class condition
void Axebaby::update( int playerX, int playerY )
{
	if(enable)
	{		
		// Apply effects of player powerup
		switch(handicap)
		{
			case 1:
			health = 0;
			break;

			case 2:
			speed = (speed / 2);
			break;

			case 3:
			power = (power / 2);
			break;

			case 4:
			speed = 0;
			break;
		}		
		
		if( playerX < x )
		{
			direction = -1;
			if( x <= playerX + 45  )
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

		if( (playerY  + 42) < y )
		{
			yVel = -speed;
		}
		else if( (playerY  + 42) > y)
		{
			yVel = speed;
		}
		else
		{
			yVel = 0;
		}
	}
}

// Attack function attempts to apply damage to player
int Axebaby::attack( int playerX, int playerY )
{

	if (  (x <= playerX + 50) && (x + 35 >= playerX) && (playerY <= y + 35) && (playerY + 50 >= y) && enable)
	{
		isAttacking = 1;
		return power;
	}
	else
	{
		return 0;
	}

}

// Clear allocated memory
void Axebaby::Free_Memory()
{
	SDL_FreeSurface( SpriteAxebaby );
	Mix_FreeChunk(spawn);
	Mix_FreeChunk(die);
}

// Reduces health
void Axebaby::applyDamage(int damage)
{
	if(damage > 0)
	{
		health -= damage;
	}
}

// Get functions
int Axebaby::getX()
{
	return x;
}

int Axebaby::getY()
{
	return y;
}

int Axebaby::getDirection()
{
	return direction;
}

int Axebaby::isDead()
{
	return Dead;
}

int Axebaby::getPoints()
{
	return points;
}

// Set functions
void Axebaby::setEnable(int e)
{
	enable = e;
}

void Axebaby::setHandicap(int h)
{
	handicap = h;
}
