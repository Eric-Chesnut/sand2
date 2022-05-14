#include "Board.h"
#include "Pixel.h"

//Using SDL, SDL_image, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <stack>

using namespace std;

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;



int main(int argc, char* args[])
{
	Board test(SCREEN_WIDTH, SCREEN_HEIGHT);
	Pixel sand(2, false, 144, 144, 144, 255);
	//test.emptyBoard();
	//test.setBorder();
	cout << test.getPosition(SCREEN_WIDTH / 2, 0).getMass() << " " << test.getPosition(SCREEN_WIDTH / 2, 2).getMass() << endl;
	test.setPosition(SCREEN_WIDTH / 2, 2, sand);
	cout << test.getPosition(SCREEN_WIDTH / 2, 3).getMass() << " " << test.getPosition(SCREEN_WIDTH / 2, 2).getMass() << endl;
	test.runSim();
	cout << test.getPosition(SCREEN_WIDTH / 2, 3).getMass() << " " << test.getPosition(SCREEN_WIDTH / 2, 2).getMass() << endl;
	return 0;
}