#include"box.h"
#include"counter.h"

Counter::Counter(int newWidth, int newHeight, int newX, int newY, int newFontSize, string newMessage, int newCountValue)
{
	setWidth(newWidth);
	setHeight(newHeight);
	setX(newX);
	setY(newY);
	
	setFontSize(newFontSize);
	setMessage(newMessage);

	renderBox();

	setCountValue(newCountValue);
}

int Counter::getCountValue()
{
	return countValue;
}

void Counter::setCountValue(int newCountValue)
{
	countValue = newCountValue;
}

int Counter::update(SDL_Event event)
{	
	string newMessage;
	ostringstream convert;
	
	convert << getCountValue();
	newMessage = convert.str();
	setMessage(newMessage);	
	renderBox();
}