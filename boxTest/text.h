#ifndef TEXT_H
#define TEXT_H

#include"box.h"
#include"SDL/SDL_ttf"

class Text : public Box
{
	friend void renderText();	
	public:
		Text(int, int, int, int, int, string);
	private:
		int size;
		TTF_font * font;
		SDL_Color textColor;
		void initialize();
};	

#endif
