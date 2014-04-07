#include"box.h"
#include"text.h"

Text::Text(int newWidth, int newHeight, int newX, int newY, int newFontSize, char * newMessage)
{
	setWidth(newWidth);
	setHeight(newHeight);
	setX(newX);
	setY(newY);
	
	setFontSize(newFontSize);
	setMessage(newMessage);
}





