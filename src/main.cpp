#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Window.h"
#include "ui/Label.h"

int main(int argc, char *argv[])
{
	if(SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO) != 0)
	{
		std::cout << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
		return -1;
	}

	if(TTF_Init() != 0)
	{
		std::cout << "Failed to initialize SDL_ttf: " << TTF_GetError() << std::endl;
		return -1;
	}

	Window window(800, 600, "LD30");

	TTF_Font *font = TTF_OpenFont("resources/ttf/Oxygen-Regular.ttf", 10);
	if(!font)
	{
		std::cout << "Failed to load font: " << TTF_GetError() << std::endl;
		return -1;
	}

	Ui::Label fpsLabel(5, 0, "", font, window.renderer());
	double lastFpsUpdate = 0;

	const uint64_t ticksPerSecond = SDL_GetPerformanceFrequency();
	bool debugText = false;
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
			else if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_F12)
			{
				debugText = !debugText;
			}
		}

		window.clear();

		if(debugText)
		{
			lastFpsUpdate += delta;
			if(lastFpsUpdate > 1)
			{
				const int fps = 1.0 / delta;
				fpsLabel.setText(std::to_string(fps).append(" FPS"));
				lastFpsUpdate = 0;
			}
			fpsLabel.draw(window.renderer());
		}

		window.flip();
	}

	TTF_Quit();
	SDL_Quit();
	return 0;
}
