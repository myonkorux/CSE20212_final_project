/******************

Chris Ray
Nathan Vahrenberg

board.h

*******************/

#include <iostream>
#include<iomanip>
#include<string>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <deque>

#include"box.h"
#include"text.h"
#include"button.h"
#include"counter.h"
#include"player.h"
#include"zombie.h"
//#include "item.h"
//#include "unit.h"

using namespace std;

class Board
{
	public:
		Board();
		void initialize();
		void display();
		void update(SDL_Event);
		void wipe();
		void clean();
		void spawnZombie();
	
	private:
		int start;
		int select;
		int game;
		int pause;
		int over;
		int difficulty;
		string diffString;

		int screenWidth;
		int screenHeight;
		int screenBPP;

		int numZombies;
		int maxZombies;

		Player player;
		deque<Zombie> zombies;
		deque<Text> textBoxes;
		deque<Button> buttons;
		deque<Counter> counters;
		//deque<Item> Items;
		//deque<Terrain> boardTerrain;

		SDL_Surface * screen;
		SDL_Surface * background;
		SDL_Event event;

		SDL_Surface * optimizeImage(string);
		void startState();
		void selectState();
		void pauseState();
		void continueGame();
		void gameState();
		void overState();
		void clearDeques();
		void stateInterpret();
		void loadBackground();
		void resetStates();
};
