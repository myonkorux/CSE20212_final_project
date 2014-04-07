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
	strcpy(message, "FOO");
	fontSize = 40;

	box.x = x;
	box.y = y;
	box.w = width;
	box.h = height;

	font = TTF_OpenFont("LIVINGBY.TTF", fontSize);
	textColor = {255, 255, 255};
	messageSurface = TTF_RenderText_Solid(font, message, textColor);	
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

void Box::setMessage(char * newMessage)
{
	strcpy(message, newMessage);
}

void Box::setFontSize(int newFontSize)
{
	fontSize = newFontSize;
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

char * Box::getMessage()
{
	return message;
}

void Box::display(SDL_Surface* destination )
{
	SDL_Rect offset;

	offset.x = getX();
	offset.y = getY();

	SDL_FillRect(destination, &box, SDL_MapRGB(destination->format, 0x00, 0x00, 0x00));

	SDL_BlitSurface( messageSurface, NULL, destination, &offset );
}
