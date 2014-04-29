/******************

Chris Ray
Nathan Vahrenberg

board.cpp

*******************/

#include "board.h"

using namespace std;

// Constructor
Board::Board()
{
	// Init values
	start = 1;
	select = 0;
	game = 0;
	gInitial = 1;
	pause = 0;
	over = 0;
	PCScore = 0;
	powerActive = 0;

	screenWidth = 880;
	screenHeight = 600;
	screenBPP = 32;

	numZombies = 0;
	maxZombies = 0;
	numBabies = 0;
	maxBabies = 0;
	numTanks = 0;
	maxTanks = 0;

	screen = NULL;
	background = NULL;

	initialize();
}

void Board::initialize()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );
	screen = SDL_SetVideoMode(screenWidth, screenHeight, screenBPP, SDL_SWSURFACE);
	TTF_Init();
	SDL_WM_SetCaption( "Zombie Slayerz", NULL );
	loadBackground();
	Player player;
	PC.push_back(player);
	setPause(1);
	Power randomPower(440, 300, 1);
	PCpower.push_back(randomPower);
	startState();
	srand(time(NULL));
	micDeath = Mix_LoadWAV("music/waves/explosion.wav");
	guitarSlow = Mix_LoadWAV("music/waves/slowMaim.wav");
	bassWeaken = Mix_LoadWAV("music/waves/stealth.wav");
	drumStun = Mix_LoadWAV("music/waves/iceLance.wav");
	createPlaylist();
	trackNumber = playlist.begin();
	spawnTerrain(23, 131, 2); //40 x 44
	spawnTerrain(109, 181, 1); //20 x 17
	spawnTerrain(136, 143, 2); //40 x 44
	spawnTerrain(837, 220, 1); //20 x 17
	spawnTerrain(800, 200, 2); //40 x 44
	spawnTerrain(834, 225, 1); //20 x 17
	display();
}

SDL_Surface * Board::optimizeImage(string filename)
{
	SDL_Surface * tempImage = NULL;
	SDL_Surface * optimized = NULL;

	tempImage = IMG_Load(filename.c_str());

	if(tempImage != NULL)
	{
		optimized = SDL_DisplayFormat(tempImage);
		SDL_FreeSurface(tempImage);

		if( optimized != NULL )
		{
		    Uint32 colorkey = SDL_MapRGB( optimized->format, 0, 0xFF, 0xFF );
		    SDL_SetColorKey( optimized, SDL_SRCCOLORKEY, colorkey );
		}
	}

	return optimized;
}

void Board::loadBackground()
{
	background = optimizeImage("sprites/newForest.jpg");
}

void Board::resetStates()
{
	start = 0;
	select = 0;
	game = 0;
	pause = 0;
	over = 0;
}

void Board::clearDeques()
{
	deque<Text>::iterator i;
	for(i = textBoxes.begin(); i != textBoxes.end(); ++i)
	{
		(i)->cleanBox();
	}	
	textBoxes.clear();

	deque<Button>::iterator j;
	for(j = buttons.begin(); j != buttons.end(); ++j)
	{
		(j)->cleanBox();
	}	
	buttons.clear();

	deque<Counter>::iterator k;
	for(k = counters.begin(); k != counters.end(); ++k)
	{
		(k)->cleanBox();
	}	
	counters.clear();
}

void Board::startState()
{	
	clearDeques();
	
	Text titleCard(720, 120, 80, 40, 110, "Zombie Slayerz");
	Text developers(720, 40, 80, 200, 30, "Developed by cray & nvahrenb");
	Text cseLabel(160, 40, 40, 550, 30, "CSE20212");
	Text versionLabel(160, 40, 680, 550, 30, "Pre-Alpha");
	textBoxes.push_back(titleCard);
	textBoxes.push_back(developers);
	textBoxes.push_back(cseLabel);
	textBoxes.push_back(versionLabel);	

	Button startButton(240, 80, 320, 280, 70, "Start");
	Button quitButton(240, 80, 320, 400, 70, "Quit");
	buttons.push_back(startButton);
	buttons.push_back(quitButton);
}

void Board::selectState()
{
	clearDeques();
	
	Button titleCard(720, 120, 80, 40, 110, "Select Difficulty");
	Button easyButton(240, 80, 320, 200, 70, "Easy");
	Button normalButton(240, 80, 320, 320, 70, "Normal");
	Button hardButton(240, 80, 320, 440, 70, "Hard");
	buttons.push_back(titleCard);
	buttons.push_back(easyButton);
	buttons.push_back(normalButton);
	buttons.push_back(hardButton);

	Text cseLabel(160, 40, 40, 550, 30, "CSE 20212");
	Text versionLabel(160, 40, 680, 550, 30, "Pre-Alpha");
	textBoxes.push_back(cseLabel);
	textBoxes.push_back(versionLabel);	
}

void Board::gameState()
{
	int a = (rand() % 100 + 1);

	if(gInitial == 1)
	{
		clearDeques();
		Counter health(160, 40, 40, 40, 30, "100", 100);
		Counter score(240, 40, 600, 40, 30, "0", PCScore);
		counters.push_back(health);
		counters.push_back(score);

		Text cseLabel(160, 40, 40, 550, 30, "Zombie Slayerz");
		Text versionLabel(160, 40, 680, 550, 30, "Pre-Alpha");
		Text diffLabel(320, 40, 280, 550, 30, diffString);
		textBoxes.push_back(cseLabel);
		textBoxes.push_back(versionLabel);
		textBoxes.push_back(diffLabel);
		
		gInitial = 0;
	}
	else
	{		
		if((a % 5) == 0)
		{			
			if(numBabies < maxBabies)
			{
				spawnBaby();
			}
			else if(numTanks < maxTanks)
			{
				spawnTank();
			}
			else if(numZombies < maxZombies)
			{
				spawnZombie();
			}
			setPause(1);
		}		

		deque<Counter>::iterator k;
		for(k = counters.begin(); k != counters.end(); ++k)
		{
			(k)->update(event);
		}
	}
}

void Board::pauseState()
{
	Button continueButton(240, 80, 320, 160, 70, "Continue");
	Button menuButton(240, 80, 320, 280, 70, "Menu");
	Button quitButton(240, 80, 320, 400, 70, "Quit");
	buttons.push_back(continueButton);
	buttons.push_back(menuButton);
	buttons.push_back(quitButton);
}

void Board::continueGame()
{
	setPause(1);

	deque<Button>::iterator j;
	for(j = buttons.begin(); j != buttons.end(); ++j)
	{
		(j)->cleanBox();
	}	
	buttons.clear();
}

void Board::overState()
{
	clearDeques();

	Text titleCard(720, 100, 80, 40, 90, "Bye, Please Close Window");
	textBoxes.push_back(titleCard);
}

void Board::stateInterpret()
{
	if(start == 1)
	{
		startState();
	}
	else if(select == 1)
	{
		selectState();
	}
	else if(game == 1)
	{
		gameState();
	}
	else if(pause == 1)
	{
		pauseState();
	}
	else if(over == 1)
	{
		overState();
	}
}

void Board::display()
{
	wipe();
	musicPlayer();
	SDL_BlitSurface(background, NULL, screen, NULL);
	
	deque<Text>::iterator i;
	for(i = textBoxes.begin(); i != textBoxes.end(); ++i)
	{
		(i)->display(screen);
	}

	deque<Button>::iterator j;
	for(j = buttons.begin(); j != buttons.end(); ++j)
	{
		(j)->display(screen);
	}

	deque<Counter>::iterator k;
	for(k = counters.begin(); k != counters.end(); ++k)
	{
		(k)->display(screen);
	}

	if(game == 1)
	{
		deque<Player>::iterator i;
		i = PC.begin();		
		(i)->display(screen);

		if(powerActive)
		{
			PCpower.begin()->display(screen);
		}

		deque<Zombie>::iterator m;
		for(m = zombies.begin(); m != zombies.end(); ++m)
		{
			(m)->display(screen);
		}

		deque<Axebaby>::iterator k;
		for(k = babies.begin(); k != babies.end(); ++k)
		{
			(k)->display(screen);
		}

		deque<Frankenstein>::iterator n;
		for(n = tanks.begin(); n != tanks.end(); ++n)
		{
			(n)->display(screen);
		}
		deque<Terrain>::iterator p;
		for(p = boardTerrain.begin(); p != boardTerrain.end(); ++p)
		{
			(p)->display(screen);
		}
	}

	SDL_Flip( screen );
}

void Board::setEvent(SDL_Event newEvent)
{
	event = newEvent;
}

void Board::update()
{
	if(start == 1)
	{
		resetStates();		
		select = (buttons.begin())->update(event);
		over = (buttons.begin() + 1)->update(event);
		if((select == 0) && (over == 0))
		{
			start = 1;
		}
		stateInterpret();	
	}
	else if(select == 1)
	{
		resetStates();	
		if((buttons.begin())->update(event) == 1)	
		{
			game = 1;
			difficulty = 4;
			maxZombies = 6;
			maxBabies = 6;
			maxTanks = 6;
			diffString = "Hardcore";
		}
		else if((buttons.begin() + 1)->update(event) == 1)	
		{
			game = 1;
			difficulty = 1;
			maxZombies = 0;
			maxBabies = 10;
			maxZombies = 0;
			maxTanks = 0;
			diffString = "Easy";
			
		}
		else if((buttons.begin() + 2)->update(event) == 1)	
		{
			game = 1;
			difficulty = 2;
			maxZombies = 7;
			maxBabies = 3;
			maxTanks = 0;
			diffString = "Normal";	
		}
		else if((buttons.begin() + 3)->update(event) == 1)	
		{
			game = 1;
			difficulty = 3;
			maxZombies = 6;
			maxBabies = 3;
			maxTanks = 1;
			diffString = "Hard";
		}
		else
		{
			select = 1;
		}
		stateInterpret();
	}
	else if(game == 1)
	{
		resetStates();
		if(event.type == SDL_KEYDOWN)
		{
			if(event.key.keysym.sym == SDLK_ESCAPE)
			{
				game = 0;				
				pause = 1;
				stateInterpret();
				return;
			}
		}

		game = 1;

		deque<Player>::iterator i;
		i = PC.begin();
		(i)->update(event);
		
		if((i->getX() >= PCpower.begin()->getX()) && (i->getX() <= PCpower.begin()->getX() + 20) && (i->getY() >= PCpower.begin()->getY()) && (i->getY() <=  PCpower.begin()->getY() + 20) && powerActive)
		{
			setHandicaps();
			powerActive = 0;
		}

		deque<Zombie>::iterator m;
		for(m = zombies.begin(); m != zombies.end(); ++m)
		{
			(m)->update((i)->getX(), (i)->getY());
			(i)->update(event);
			(m)->applyDamage((i)->attack((m)->getX(), (m)->getY()));
			(i)->apply_damage((m)->attack((i)->getX(), (i)->getY()),(m)->getDirection());
			(counters.begin())->setCountValue((i)->getHealth());

			if((i)->isDead() == 1)
			{
				game = 0;					
				over = 1;
				break;
			}
			else if((m)->isDead() == 1)
			{
				PCScore += ((m)->getPoints());
				(counters.begin() + 1)->setCountValue(PCScore);
				(m)->Free_Memory();
				zombies.erase(m);
				numZombies--;
				break;
			}
		}

		(i)->update(event);

		if((i->getX() >= PCpower.begin()->getX()) && (i->getX() <= PCpower.begin()->getX() + 20) && (i->getY() >= PCpower.begin()->getY()) && (i->getY() <=  PCpower.begin()->getY() + 20) && powerActive)
		{
			setHandicaps();
			powerActive = 0;
		}	
		
		deque<Axebaby>::iterator k;
		for(k = babies.begin(); k != babies.end(); ++k)
		{
			(k)->update((i)->getX(), (i)->getY());
			(i)->update(event);
			(k)->applyDamage((i)->attack((k)->getX(), (k)->getY()));
			(i)->apply_damage((k)->attack((i)->getX(), (i)->getY()),(k)->getDirection());
			(counters.begin())->setCountValue((i)->getHealth());

			if((i)->isDead() == 1)
			{
				game = 0;					
				over = 1;
				break;
			}
			else if((k)->isDead() == 1)
			{
				PCScore += ((k)->getPoints());
				(counters.begin() + 1)->setCountValue(PCScore);
				(k)->Free_Memory();
				babies.erase(k);
				numBabies--;
				break;
			}
		}

		(i)->update(event);

		if((i->getX() >= PCpower.begin()->getX()) && (i->getX() <= PCpower.begin()->getX() + 20) && (i->getY() >= PCpower.begin()->getY()) && (i->getY() <=  PCpower.begin()->getY() + 20) && powerActive)
		{
			setHandicaps();
			powerActive = 0;
		}
		
		deque<Frankenstein>::iterator n;
		for(n = tanks.begin(); n != tanks.end(); ++n)
		{
			(n)->update((i)->getX(), (i)->getY());
			(i)->update(event);
			(n)->applyDamage((i)->attack((n)->getX(), (n)->getY()));
			(i)->apply_damage((n)->attack((i)->getX(), (i)->getY()),(n)->getDirection());
			(counters.begin())->setCountValue((i)->getHealth());

			if((i)->isDead() == 1)
			{
				game = 0;					
				over = 1;
				break;
			}
			else if((n)->isDead() == 1)
			{
				PCScore += ((n)->getPoints());
				(counters.begin() + 1)->setCountValue(PCScore);
				(n)->Free_Memory();
				tanks.erase(n);
				numTanks--;
				break;
			}
		}

		stateInterpret();
	}
	else if(pause == 1)
	{
		setPause(0);		
		if((buttons.begin())->update(event) == 1)	
		{
			game = 1;
			continueGame();
		}
		else if((buttons.begin() + 1)->update(event) == 1)	
		{
			resetStates();
			gInitial = 1;	

			deque<Zombie>::iterator i;
			for(i = zombies.begin(); i != zombies.end(); ++i)
			{
				(i)->Free_Memory();
			}
			zombies.clear();
			numZombies = 0;
		
			deque<Axebaby>::iterator j;
			for(j = babies.begin(); j != babies.end(); ++j)
			{
				(j)->Free_Memory();
			}
			babies.clear();
			numBabies = 0;

			deque<Frankenstein>::iterator k;
			for(k = tanks.begin(); k != tanks.end(); ++k)
			{
				(k)->Free_Memory();
			}
			tanks.clear();
			numTanks = 0;			

			resetPC();
			Player player;
			PC.push_back(player);		
			start = 1;
			stateInterpret();
		}
		else if((buttons.begin() + 2)->update(event) == 1)	
		{
			resetStates();				
			over = 1;
			stateInterpret();
		}
	}

	if(((PCScore % 100) == 0) && (PCScore != 0))
	{
		(PCpower.begin())->setType(rand()%4 + 1);
		powerActive = 1;
	}

	display();
}

void Board::wipe()
{
	// Fill with white space
	SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 255, 255, 255 ) );
}

void Board::clean()
{
	clearDeques();
	SDL_FreeSurface(background);

	deque<Zombie>::iterator i;
	for(i = zombies.begin(); i != zombies.end(); ++i)
	{
		(i)->Free_Memory();
	}
	zombies.clear();
	numZombies = 0;
		
	deque<Axebaby>::iterator j;
	for(j = babies.begin(); j != babies.end(); ++j)
	{
		(j)->Free_Memory();
	}
	babies.clear();
	numBabies = 0;

	deque<Frankenstein>::iterator k;
	for(k = tanks.begin(); k != tanks.end(); ++k)
	{
		(k)->Free_Memory();
	}
	tanks.clear();
	numTanks = 0;

	deque<Terrain>::iterator m;
	for(m = boardTerrain.begin(); m != boardTerrain.end(); ++m)
	{
		(m)->Free_Memory();
	}

	for(trackNumber = playlist.begin(); trackNumber != playlist.end(); ++trackNumber)
	{
		Mix_FreeMusic(*trackNumber);
	}

	Mix_FreeChunk(micDeath);
	Mix_FreeChunk(guitarSlow);
	Mix_FreeChunk(bassWeaken);
	Mix_FreeChunk(drumStun);				

	resetPC();

	TTF_Quit();
	Mix_CloseAudio();
	SDL_Quit();
}

void Board::spawnZombie()
{
	Zombie basicZombie;
	zombies.push_back(basicZombie);
	numZombies++;
}

void Board::spawnBaby()
{
	Axebaby baby;
	babies.push_back(baby);
	numBabies++;
}

void Board::spawnTank()
{
	Frankenstein tank;
	tanks.push_back(tank);
	numTanks++;
}

void Board::spawnTerrain(int newX, int newY, int newType)
{
	Terrain t1( newX, newY, newType );
	boardTerrain.push_back( t1 );
}

void Board::resetPC()
{
	deque<Player>::iterator i;
	i = PC.begin();
	(i)->Free_Memory();
	PC.clear();

	PCScore = 0;
}

void Board::setPause(int p)
{
	deque<Player>::iterator i;
	i = PC.begin();
	(i)->setEnable(p);
	
	deque<Zombie>::iterator j;
	for(j = zombies.begin(); j != zombies.end(); ++j)
	{
		(j)->setEnable(p);
	}
		
	deque<Axebaby>::iterator k;
	for(k = babies.begin(); k != babies.end(); ++k)
	{
		(k)->setEnable(p);
	}

	deque<Frankenstein>::iterator m;
	for(m = tanks.begin(); m != tanks.end(); ++m)
	{
		(m)->setEnable(p);
	}
}

void Board::setHandicaps()
{
	switch(PCpower.begin()->getType())
	{
		case 1:
		Mix_PlayChannel(-1, micDeath, 0);
		break;

		case 2:
		Mix_PlayChannel(-1, guitarSlow, 0);
		break;
	
		case 3:
		Mix_PlayChannel(-1, bassWeaken, 0);
		break;

		case 4:
		Mix_PlayChannel(-1, drumStun, 0);
		break;
	}	

	deque<Zombie>::iterator i;
	for(i = zombies.begin(); i != zombies.end(); ++i)
	{
		(i)->setHandicap(PCpower.begin()->getType());
	}

	deque<Axebaby>::iterator j;
	for(j = babies.begin(); j != babies.end(); ++j)
	{
		(j)->setHandicap(PCpower.begin()->getType());
	}

	deque<Frankenstein>::iterator k;
	for(k = tanks.begin(); k != tanks.end(); ++k)
	{
		(k)->setHandicap(PCpower.begin()->getType());
	}
}

void Board::createPlaylist()
{
	Mix_Music * song0 = Mix_LoadMUS("music/waves/runToTheHills.wav");
	playlist.push_back(song0);
	Mix_Music * song1 = Mix_LoadMUS("music/waves/puppets.wav");
	playlist.push_back(song1);
	Mix_Music * song2 = Mix_LoadMUS("music/waves/spades.wav");
	playlist.push_back(song2);
	Mix_Music * song3 = Mix_LoadMUS("music/waves/crazyTrain.wav");
	playlist.push_back(song3);
	Mix_Music * song4 = Mix_LoadMUS("music/waves/iron.wav");
	playlist.push_back(song4);
	Mix_Music * song5 = Mix_LoadMUS("music/waves/beast.wav");
	playlist.push_back(song5);
	Mix_Music * song6 = Mix_LoadMUS("music/waves/warPigs.wav");
	playlist.push_back(song6);
	Mix_Music * song7 = Mix_LoadMUS("music/waves/paranoid.wav");
	playlist.push_back(song7);
	Mix_Music * song8 = Mix_LoadMUS("music/waves/enterSandman.wav");
	playlist.push_back(song8);
	Mix_Music * song9 = Mix_LoadMUS("music/waves/metal.wav");
	playlist.push_back(song9);
	Mix_Music * song10 = Mix_LoadMUS("music/waves/special.wav");
	playlist.push_back(song10);
}

void Board::musicPlayer()
{
	if(Mix_PlayingMusic() == 0)
	{
		Mix_PlayMusic(*trackNumber, 1);
		++trackNumber; 
	}
	
	if(trackNumber == playlist.end())
	{
		trackNumber = playlist.begin();
	}
}



