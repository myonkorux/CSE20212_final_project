#include"box.h"
#include"text.h"

Text::Text(int newWidth, int newHeight, int newX, int newY, int fontSize, string newMessage)
{
	setWidth(newWidth);
	setHeight(newHeight);
	setX(newX);
	setY(newY);

	size = fontSize;
	
	message = newMessage;

	initialize();
}

void Text::initialize()
{
	TTF_Init();

	textColor = {255, 255, 255};
	
	font = TTF_OpenFont("LIVINGBY.TTF", size);
}




