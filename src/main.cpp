#include <iostream>

#include <SDL2/SDL.h>

#include "Window.h"

int main(int argc, char *argv[])
{
	if(SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO) != 0)
	{
		std::cout << "Failed to initialize SDL: " << SDL_GetError();
		return -1;
	}

	Window window(800, 600, "LD30");

	const uint64_t ticksPerSecond = SDL_GetPerformanceFrequency();
	uint64_t lastTicks = SDL_GetPerformanceCounter();
	while(window.isOpen())
	{
		const uint64_t currentTicks = SDL_GetPerformanceCounter();
		const double delta = (double)(currentTicks - lastTicks) / ticksPerSecond;
		lastTicks = currentTicks;

		SDL_Event event;
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
			{
				window.close();
			}
		}

		window.clear();

		// Draw stuff here

		window.flip();
	}

	SDL_Quit();
	return 0;
}
