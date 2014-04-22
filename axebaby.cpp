/******************

Chris Ray
Nathan Vahrenberg

*******************/

#include <iostream>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#include "axebaby.h"

void apply_axebaby_sprite( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL ){

	SDL_Rect offset;
	
	offset.x = x;
	offset.y = y;
	
	SDL_BlitSurface( source, clip, destination, &offset );

}

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
		    Uint32 colorkey = SDL_MapRGB( optimized->format, 8, 112, 80 );
		    SDL_SetColorKey( optimized, SDL_SRCCOLORKEY, colorkey );
		}
	}

	return optimized;
}

Axebaby::Axebaby(){

	x = 400;
	y = 318;
	xVel = 0;
	yVel = 0;
	direction = 1;
	health = 10;
	speed = 4;
	power = 20;
	isStanding = 1;
	isAttacking = 0;
	Dead = 0;
	points = 20;
	
	clipSelect = 0;
	
	SpriteAxebaby = optimizeImage("sprites/axebaby.bmp");
	
	int i;
	
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
	attacking[0].h = 198;
	
	attackingL[0].x = 4;
	attackingL[0].w = 31-4;
	attackingL[0].y = 172;
	attackingL[0].h = 198;

}

void Axebaby::display( SDL_Surface* source )
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

void Axebaby::update( int playerX, int playerY )
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

int Axebaby::attack( int playerX, int playerY )
{

	if ( ((x <= playerX + 50) && (x + 35 >= playerX)) && (playerY == y) )
	{
		isAttacking = 1;
		return power;
	}
	else
	{
		return 0;
	}

}

void Axebaby::Free_Memory(){

	SDL_FreeSurface( SpriteAxebaby );

}

void Axebaby::applyDamage(int damage)
{
	if(damage > 0)
	{
		health -= damage;
	}
}

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

void Axebaby::setEnable(int e)
{
	enable = e;
}
