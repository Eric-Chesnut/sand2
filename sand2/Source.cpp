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

//Starts up SDL and creates window
bool init();

//Frees media and shuts down SDL
void close();

//draws the screen
void drawScreen(Board *toDraw);

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;



bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			}
		}
	}
	return success;
}

//garbage collection
void close()
{


	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}


//draws the screen
void drawScreen(Board* toDraw)
{//empties board
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);
	for (int y = 0; y < SCREEN_HEIGHT; y++)
	{
		for (int x = 0; x < SCREEN_WIDTH; x++)
		{
			SDL_SetRenderDrawColor(gRenderer, toDraw->getPosition(x,y).getR(), toDraw->getPosition(x,y).getG(), toDraw->getPosition(x,y).getB(), toDraw->getPosition(x,y).getA());
			SDL_RenderDrawPoint(gRenderer, x, y);
		}
	}
	SDL_RenderPresent(gRenderer);
}

int main(int argc, char* args[])
{
	init();
	Board test(SCREEN_WIDTH, SCREEN_HEIGHT);
	Pixel sand(2, false, 144, 144, 144, 255);
	Pixel water(1, true, 0, 0, 255, 0xFF);
	//test.emptyBoard();
	//test.setBorder();
	cout << test.getPosition(SCREEN_WIDTH / 2, 0).getMass() << " " << test.getPosition(SCREEN_WIDTH / 2, 2).getMass() << endl;
	test.setPosition(SCREEN_WIDTH / 2, 2, sand);
	cout << test.getPosition(SCREEN_WIDTH / 2, 3).getMass() << " " << test.getPosition(SCREEN_WIDTH / 2, 2).getMass() << endl;
	test.runSim();
	cout << test.getPosition(SCREEN_WIDTH / 2, 3).getMass() << " " << test.getPosition(SCREEN_WIDTH / 2, 2).getMass() << endl;
	bool quit = false;
	SDL_Event e;
	int wet = 100;
	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}
		test.runSim();
		drawScreen(&test);
		//if(donee > 0)
		//{ 
		
		//donee--;
		test.setPosition(SCREEN_WIDTH / 2, 2, sand);
		if (wet > 0)
		{
			test.setPosition(3*SCREEN_WIDTH / 4, 2, water);
			wet--;
		}
	//}

	}
	close();
	return 0;
}