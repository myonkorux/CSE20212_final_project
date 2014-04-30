/******************

Chris Ray
Nathan Vahrenberg

board.h

*******************/

#include <iostream>
#include<iomanip>
#include<string>
#include<cstdlib>
#include<ctime>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include <deque>

#include"box.h"
#include"text.h"
#include"button.h"
#include"counter.h"
#include"player.h"
#include"zombie.h"
#include"axebaby.h"
#include "frankenstein.h"
#include "Power.h"
#include "terrain.h"

using namespace std;

class Board
{
	public:
		Board();
		void update();
		void clean();
		void setEvent(SDL_Event);
	
	private:
		// States
		int start;
		int select;
		int game;
		int gInitial;
		int pause;
		int over;
		// Game properties
		int difficulty;
		int PCScore;
		int powerActive;
		string diffString;
		// Window properties
		int screenWidth;
		int screenHeight;
		int screenBPP;
		// Number (and max number) of mobs
		int numZombies;
		int maxZombies;
		int numBabies;
		int maxBabies;
		int numTanks;
		int maxTanks;
		
		// Sounds
		deque<Mix_Music *>::iterator trackNumber;

		// Player deque (only single player, but uses deque to make display easier)
		deque<Player> PC;
		deque<Power> PCpower;

		// Mob deques
		deque<Zombie> zombies;
		deque<Axebaby> babies;
		deque<Frankenstein> tanks;
		
		// Inanimate object deques
		deque<Text> textBoxes;
		deque<Button> buttons;
		deque<Counter> counters;
		deque<Terrain> boardTerrain;
		deque<Mix_Music *> playlist;

		// Display elements
		SDL_Surface * screen;
		SDL_Surface * background;
		
		// Powerup sounds
		Mix_Chunk * micDeath;
		Mix_Chunk * guitarSlow;
		Mix_Chunk * bassWeaken;
		Mix_Chunk * drumStun;
		
		SDL_Event event;

		SDL_Surface * optimizeImage(string);
		
		// Function prototypes
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
		void resetPC();
		void spawnZombie();
		void spawnBaby();
		void spawnTank();
		void spawnTerrain(int, int, int);
		void initialize();
		void display();
		void wipe();
		void setPause(int);
		void setHandicaps();
		void createPlaylist();
		void musicPlayer();
};
