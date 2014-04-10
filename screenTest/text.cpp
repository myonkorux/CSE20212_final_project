#include"box.h"
#include"text.h"

Text::Text(int newWidth, int newHeight, int newX, int newY, int newFontSize, string newMessage)
{
	setWidth(newWidth);
	setHeight(newHeight);
	setX(newX);
	setY(newY);
	
	setFontSize(newFontSize);
	setMessage(newMessage);

	renderBox();
}

int Text::update(SDL_Event event)
{
	//noot noot
}




