/******************

Chris Ray
Nathan Vahrenberg

*******************/

#include <iostream>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#include "frankenstein.h"

void apply_frankenstein_sprite( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL ){

	SDL_Rect offset;
	
	offset.x = x;
	offset.y = y;
	
	SDL_BlitSurface( source, clip, destination, &offset );

}

SDL_Surface * Frankenstein::optimizeImage(string filename)
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
		    Uint32 colorkey = SDL_MapRGB( optimized->format, 0, 0, 0 );
		    SDL_SetColorKey( optimized, SDL_SRCCOLORKEY, colorkey );
		}
	}

	return optimized;
}

Frankenstein::Frankenstein(){

	x = rand()%800+40;
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
	power = 20;
	isStanding = 1;
	isAttacking = 0;
	Dead = 0;
	enable = 0;
	isDying = 0;
	handicap = 0;
	points = 30;

	spawn = Mix_LoadWAV("music/waves/tankSpawn.wav");
	die = Mix_LoadWAV("music/waves/tankDeath.wav");
	Mix_PlayChannel(-1, spawn, 0);
		
	
	clipSelect = 0;
	
	SpriteFrankenstein = optimizeImage("sprites/frankenstein.bmp");
	
	int i;
	
	for( i = 0; i <= 4; i++ ){
		moving[i].y = 15;
		moving[i].h = 65-15;
		movingL[i].y = 15;
		movingL[i].h = 65-15;
	}
	
	movingL[0].x = 30;
	movingL[0].w = 70-30;
	movingL[1].x = 70;
	movingL[1].w = 110-70;
	movingL[2].x = 110;
	movingL[2].w = 150-110;
	movingL[3].x = 150;
	movingL[3].w = 190-150;
	
	moving[0].x = 200;
	moving[0].w = 240-200;
	moving[1].x = 240;
	moving[1].w = 280-240;
	moving[2].x = 280;
	moving[2].w = 320-280;
	moving[3].x = 320;
	moving[3].w = 360-320;
	
	dying[0].x = 85;
	dying[0].w = 140-85;
	dying[1].x = 140;
	dying[1].w = 195-140;
	dying[2].x = 195;
	dying[2].w = 250-195;
	dying[3].x = 250;
	dying[3].w = 305-250;
	dying[4].x = 140;
	dying[4].w = 160-140;
	dying[5].x = 160;
	dying[5].w = 180-160;
	dying[6].x = 180;
	dying[6].w = 200-180;
	dying[7].x = 200;
	dying[7].w = 220-200;
	dying[8].x = 220;
	dying[8].w = 240-220;
	dying[9].x = 240;
	dying[9].w = 260-240;
	
	dying[0].y = 130;
	dying[0].h = 195-130;
	dying[1].y = 130;
	dying[1].h = 195-130;
	dying[2].y = 130;
	dying[2].h = 195-130;
	dying[3].y = 130;
	dying[3].h = 195-130;
	dying[4].y = 410;
	dying[4].h = 450-410;
	dying[5].y = 410;
	dying[5].h = 450-410;
	dying[6].y = 410;
	dying[6].h = 450-410;
	dying[7].y = 410;
	dying[7].h = 450-410;
	dying[8].y = 410;
	dying[8].h = 450-410;
	dying[9].y = 410;
	dying[9].h = 450-410;
	
	
}

void Frankenstein::display( SDL_Surface* source )
{	
	int tempX = 0;
	int tempY = 0;

	if((health <= 0) && (isDying == 0))
	{
		Mix_PlayChannel(-1, die, 0);		
		isDying = 1;
		clipSelect = 0;
	}

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
	
	if(isDying)
	{
		apply_frankenstein_sprite( x, y, SpriteFrankenstein, source, &dying[ clipSelect ]);
	}
	else if (direction == 1)
	{
		apply_frankenstein_sprite( x, y, SpriteFrankenstein, source, &moving[ clipSelect ]);
	}
	else
	{
		apply_frankenstein_sprite( x, y, SpriteFrankenstein, source, &movingL[ clipSelect ]);
	}

	clipSelect++;
}

void Frankenstein::update( int playerX, int playerY )
{
	if(enable)
	{		
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

int Frankenstein::attack( int playerX, int playerY )
{

	if ( (x <= playerX + 50) && (x + 35 >= playerX) && (playerY <= y + 35) && (playerY + 50 >= y) && enable)
	{
		return power;
	}
	else
	{
		return 0;
	}

}

void Frankenstein::Free_Memory()
{
	Mix_FreeChunk(spawn);
	Mix_FreeChunk(die);
	SDL_FreeSurface( SpriteFrankenstein );
}

void Frankenstein::applyDamage(int damage)
{
	if(damage > 0)
	{
		health -= damage;
	}
}

int Frankenstein::getX()
{
	return x;
}

int Frankenstein::getY()
{
	return y;
}

int Frankenstein::getDirection()
{
	return direction;
}

int Frankenstein::isDead()
{
	return Dead;
}

int Frankenstein::getPoints()
{
	return points;
}

void Frankenstein::setEnable(int e)
{
	enable = e;
}

void Frankenstein::setHandicap(int h)
{
	handicap = h;
}
