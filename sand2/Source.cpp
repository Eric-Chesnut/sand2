#include "Board.h"
#include "Pixel.h"
#include "Utilities.h"


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

void drawScreen2(Board *toDraw);

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Texture for renderer
SDL_Texture* gTexture = NULL;

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

				//create texture
				gTexture = SDL_CreateTexture(gRenderer, SDL_PIXELFORMAT_ARGB8888,
					SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);
				if (gTexture == NULL)
				{
					printf("Texture could not be created! SDL Error: %s\n", SDL_GetError());
					success = false;
				}
			}
		}
	}
	return success;
}

//garbage collection
void close()
{


	//Destroy window	
	SDL_DestroyTexture(gTexture);
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;
	gTexture = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}


//hopefully faster way to draw the screen
void drawScreen2(Board* toDraw)
{
	// The Back Buffer texture may be stored with an extra bit of width (pitch) on the video card in order to properly
	// align it in VRAM should the width not lie on the correct memory boundary (usually four bytes).
	int32_t pitch = 0;

	// This will hold a pointer to the memory position in VRAM where our Back Buffer texture lies
	uint32_t* pPixelBuffer = nullptr;

	// Lock the memory in order to write our Back Buffer image to it
	if (!SDL_LockTexture(gTexture, NULL, (void**)&pPixelBuffer, &pitch))
	{
		// The pitch of the Back Buffer texture in VRAM must be divided by four bytes
		// as it will always be a multiple of four
		pitch /= sizeof(uint32_t);
		for (uint32_t i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; ++i)
		{
			switch (toDraw->getPosition(i))
			{
			case 1:
				pPixelBuffer[i] = ARGB(144,144,144,255);
				//SDL_SetRenderDrawColor(gRenderer, 144, 144, 144, 255);
				//SDL_RenderDrawPoint(gRenderer, x, y);
				break;
			case 0:
				pPixelBuffer[i] = ARGB(255, 255, 255, 255);
				break;
			case -1:
				pPixelBuffer[i] = ARGB(0, 0, 0, 255);
				//SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
				//SDL_RenderDrawPoint(gRenderer, x, y);
				break;
			}
		}
		// Unlock the texture in VRAM to let the GPU know we are done writing to it
		SDL_UnlockTexture(gTexture);

		// Copy our texture in VRAM to the display framebuffer in VRAM
		SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

		// Copy the VRAM framebuffer to the display
		SDL_RenderPresent(gRenderer);
	}
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
			switch (toDraw->getPosition(x, y))
			{
			case 1:
				SDL_SetRenderDrawColor(gRenderer, 144, 144, 144, 255);
				SDL_RenderDrawPoint(gRenderer, x, y);
				break;
			case -1:
				SDL_SetRenderDrawColor(gRenderer, 0,0,0,255);
				SDL_RenderDrawPoint(gRenderer, x, y);
				break;
			}
		}
	}
	SDL_RenderPresent(gRenderer);
}

int main(int argc, char* args[])
{
	init();
	Board test(SCREEN_WIDTH, SCREEN_HEIGHT);
	//Pixel sand(2, false, 144, 144, 144, 255);
	//Pixel water(1, true, 0, 0, 255, 0xFF);
	//test.emptyBoard();
	//test.setBorder();
	cout << test.getPosition(SCREEN_WIDTH / 2, 0) << " " << test.getPosition(SCREEN_WIDTH / 2, 2) << endl;
	test.setPosition(SCREEN_WIDTH / 2, 2, 1);
	cout << test.getPosition(SCREEN_WIDTH / 2, 3) << " " << test.getPosition(SCREEN_WIDTH / 2, 2) << endl;
	test.runSim();
	cout << test.getPosition(SCREEN_WIDTH / 2, 3) << " " << test.getPosition(SCREEN_WIDTH / 2, 2) << endl;
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
		drawScreen2(&test);

		//drawScreen(&test);
		//if(donee > 0)
		//{ 
		
		//donee--;
		test.setPosition(SCREEN_WIDTH / 2, 2, 1);
		/*if (wet > 0)
		{
			test.setPosition(3*SCREEN_WIDTH / 4, 2, water);
			wet--;
		}*/
	//}

	}
	close();
	return 0;
}