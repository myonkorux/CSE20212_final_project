//Christopher Ray
//Professor Scott
//CSE 20212

//moveMain.cpp
//Driver program for move

#include"Screen.h"

using namespace std;

int main(int argc, char * args[])
{
	Screen screenTest;
	screenTest.initialize();
	screenTest.animate();
	screenTest.cleanUp();
	return 0;
}
