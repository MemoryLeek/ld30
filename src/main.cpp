#include <assert.h>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "states/SplashState.h"
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

	TTF_Font *font = TTF_OpenFont("resources/ttf/Oxygen-Regular.ttf", 10);
	if(!font)
	{
		std::cout << "Failed to load font: " << TTF_GetError() << std::endl;
		return -1;
	}

	SDL_Window *window = SDL_CreateWindow("LD30", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_OPENGL);
	assert(window);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	assert(renderer);

	IState *currentState = new SplashState(renderer);

	Ui::Label fpsLabel(5, 0, "", font, renderer);
	double lastFpsUpdate = 0;

	const uint64_t ticksPerSecond = SDL_GetPerformanceFrequency();
	bool debugText = false;
	uint64_t lastTicks = SDL_GetPerformanceCounter();
	for(bool shouldRun = true; shouldRun && currentState;)
	{
		const uint64_t currentTicks = SDL_GetPerformanceCounter();
		const double delta = (double)(currentTicks - lastTicks) / ticksPerSecond;
		lastTicks = currentTicks;

		SDL_Event event;
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
			{
				shouldRun = false;
			}
			else if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_F12)
			{
				debugText = !debugText;
			}
		}

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);

		IState *newState = currentState->update(delta);
		if(newState != currentState)
		{
			delete currentState;
			currentState = newState;
		}

		if(debugText)
		{
			lastFpsUpdate += delta;
			if(lastFpsUpdate > 1)
			{
				const int fps = 1.0 / delta;
				fpsLabel.setText(std::to_string(fps).append(" FPS"));
				lastFpsUpdate = 0;
			}
			fpsLabel.draw(renderer);
		}

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	TTF_Quit();
	SDL_Quit();
	return 0;
}
