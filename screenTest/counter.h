#ifndef COUNTER_H
#define COUNTER_H

#include"box.h"
#include<sstream>

class Counter : public Box
{
	public:
		Counter(int, int, int, int, int, string, int = 0);
		int getCountValue();
		void setCountValue(int);
		virtual void update(SDL_Event);
	private:
		int countValue;	
};

#endif
