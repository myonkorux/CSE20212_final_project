#ifndef BUTTON_H
#define BUTTON_H

#include"box.h"

class Button : public Box
{
	public:
		Button(int, int, int, int, int, string);
		virtual void update(SDL_Event);
};

#endif
