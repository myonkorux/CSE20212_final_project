//Christopher Ray, Nathan Vahrenberg
//Professor Scott
//CSE 20212
//29 April 2014

//text.h
//Header file for Text class, for use with text.cpp in slayerz

#ifndef TEXT_H
#define TEXT_H

#include"box.h"

class Text : public Box 				//text class inherits from box
{
	public:
		Text(int, int, int, int, int, string); 	//constructor
		virtual int update(SDL_Event ); 	//dummy update function (only here due to requirements of inheritance/polymorphism)
};	

#endif
