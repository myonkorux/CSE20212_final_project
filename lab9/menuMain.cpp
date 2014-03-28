//Christopher Ray, Nathan Vahrenberg
//Professor Scott
//CSE 20212 
//27 March 2014

//menuMain.cpp
//driver program for menu

#include"Menu.h"

int main(int argc, char* args[])
{
	Menu myMenu; 		//declaring myMenu 
	myMenu.initialize(); 	//initializing myMenu (initializing SDL/SDL_ttf and uploading images and text)
	myMenu.displayMenu(); 	//displaying the menu
	myMenu.Clean(); 	//clearing the images and text and closing SDL/SDL_ttf once the screen is closed	
	return 0;
}
