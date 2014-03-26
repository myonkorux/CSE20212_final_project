/******************

Chris Ray
Nathan Vahrenberg

board.h

*******************/

#include <iostream>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <deque>

using namespace std;

class Board{

	public:
		Board();
		void display();
		void update();
		void clean();
	
	private:
		int start;
		int game;
		int pause;
		int over;
		Player player;
		deque<Zombie> zombies;
		deque<Text> textboxes;
		deque<Button> buttons;
		deque<Counter> counters;
		deque<PowerUp> PowerUps;
		deque<Terrain> boardTerrain;

};
