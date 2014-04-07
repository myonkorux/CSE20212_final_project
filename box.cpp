/******************

Chris Ray
Nathan Vahrenberg

box.cpp

*******************/

#include "box.h"

using namespace std;

// Constructor
Box::Box()
{
	height = 100;
	width = 100;
	x = 0;
	y = 0;

	box.x = x;
	box.y = y;
	box.w = width;
	box.h = height;
}

void Box::setX(int newX)
{
	x = newX;
	box.x = x;
}

void Box::setY(int newY)
{
	y = newY;
	box.y = y;
}

void Box::setHeight(int newHeight)
{
	height = newHeight;
	box.h = height;
}

void Box::setWidth(int newWidth)
{
	width = newWidth;
	box.w = width;
}

void Box::setMessage(string newMessage)
{
	message = newMessage;
}

int Box::getX()
{
	return x;
}

int Box::getY()
{
	return y;
}

int Box::getHeight()
{
	return height;
}

int Box::getWidth()
{
	return width;
}

void Box::display(SDL_Surface* destination )
{
	SDL_Rect offset;

	offset.x = getX();
	offset.y = getY();

	SDL_BlitSurface( /*box*/ NULL, NULL, destination, &offset );
}

void Box::renderBox()
{
	
}
