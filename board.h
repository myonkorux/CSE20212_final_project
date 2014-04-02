/******************

Chris Ray
Nathan Vahrenberg

board.h

*******************/

#include <iostream>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <deque>

#include "box.h"
#include "item.h"
#include "unit.h"

using namespace std;

class Board{

	public:
		Board();
		void display();
		void update( SDL_Surface* );
		void clean( SDL_Surface* );
	
	private:
		int start;
		int game;
		int pause;
		int over;
		//Player player;
		//deque<Zombie> zombies;
		deque<Box> textboxes;
		//deque<Button> buttons;
		//deque<Counter> counters;
		deque<Item> Items;
		//deque<Terrain> boardTerrain;

};
