






#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <windows.h>
#include <ctime>
#include "World.h"


bool loop(int& inputDir)
{
	SDL_Event event;

	while (SDL_PollEvent(&event)) 
	{
		switch (event.type) 
		{
		case SDL_KEYDOWN:
		case SDL_KEYUP:
			
			//SDLK_RIGHT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RIGHT),
			//	SDLK_LEFT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LEFT),
			//	SDLK_DOWN = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_DOWN),
			//	SDLK_UP = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_UP),

			if (event.key.keysym.sym == SDLK_LEFT)
			{
				inputDir = Left;
			}
			else if (event.key.keysym.sym == SDLK_RIGHT)
			{
				inputDir = Right;
			}
			else if (event.key.keysym.sym == SDLK_UP)
			{
				inputDir = Up;
			}
			else if (event.key.keysym.sym == SDLK_DOWN)
			{
				inputDir = Down;
			}

			
			//std::cout << event.key.keysym.sym << "  " << SDL_GetKeyName(event.key.keysym.sym) << std::endl;
			//Utility::PrintKey(&event.key.keysym, (event.key.state == SDL_PRESSED) ? SDL_TRUE : SDL_FALSE, (event.key.repeat) ? SDL_TRUE : SDL_FALSE);
			break;
		
		case SDL_QUIT:
			return false;
		default:
			break;
		}
	}
	return true;
}

int main(int argc, char *argv[])
{
	// sdl
	{
		AllocConsole();

		SDL_Window *window;

		// Enable standard application logging 
		SDL_LogSetPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO);

		// Initialize SDL
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s\n", SDL_GetError());
			return (1);
		}

		// Set 640x480 video mode
		window = SDL_CreateWindow(
			"CheckKeys Test",
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			640, 480, 0);
		if (!window)
		{
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create 640x480 window: %s\n",
				SDL_GetError());
			Utility::quit(2);
		}

		SDL_StartTextInput();

		// Print initial modifier state 
		SDL_PumpEvents();
		Utility::PrintModifierState();
	}
	


	srand((unsigned int)time(0));
	World world;

	world.init();
	int stepCnt = 0;

	while (true) 
	{
		// input
		int inputDir = -1;
		loop(inputDir);
			
		if (!world.update(inputDir))
		{
			break;
		}
		
		stepCnt++;
		Sleep(50);
	}

	SDL_Quit();
	return (0);
}

