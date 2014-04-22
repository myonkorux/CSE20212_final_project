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
		    Uint32 colorkey = SDL_MapRGB( optimized->format, 8, 112, 80 );
		    SDL_SetColorKey( optimized, SDL_SRCCOLORKEY, colorkey );
		}
	}

	return optimized;
}

Frankenstein::Frankenstein(){

	x = 400;
	y = 318;
	xVel = 0;
	yVel = 0;
	direction = 1;
	health = 30;
	speed = 1;
	power = 30;
	isStanding = 1;
	isAttacking = 0;
	Dead = 0;
	
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

}

void Frankenstein::display( SDL_Surface* source )
{	
	int tempX = 0;
	int tempY = 0;

	if(health <= 0)
	{
		Dead = 1;
		return;
	}

	tempX = (x + xVel);
	tempY = (y + yVel);
	if((tempX > 0) && (tempX < 840))
	{
		x = tempX;
	}
	if((tempY > 0) && (tempY < 540))
	{
		y = tempY;
	}
	
	if( clipSelect >= 4 )
	{
		clipSelect = 0;
	}

	if( clipSelect >= 3 )
	{
		clipSelect = 0;
	}
	
	if (direction == 1)
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

int Frankenstein::attack( int playerX, int playerY )
{

	if ( ((x <= playerX + 50) && (x + 35 >= playerX)) && (playerY == y) )
	{
		return power;
	}
	else
	{
		return 0;
	}

}

void Frankenstein::Free_Memory(){

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
