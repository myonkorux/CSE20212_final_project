#ifndef TEXT_H
#define TEXT_H

#include"box.h"

class Text : public Box
{
	public:
		Text(int, int, int, int, int, string);
		virtual void update(SDL_Event );
};	

#endif
