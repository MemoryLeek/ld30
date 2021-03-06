#include <assert.h>
#include <algorithm>
#include <iostream>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Renderer.h"
#include "StateHandler.h"
#include "DefaultSettingsProvider.h"
#include "SettingsProvider.h"
#include "SettingsHandler.h"
#include "SoundHandler.h"
#include "MapSelectionToken.h"

#include "states/MainMenuState.h"
#include "states/SplashState.h"

#include "ui/Label.h"

#undef main

int main(int argc, char *argv[])
{
	std::vector<std::string> arguments(argv + 1, argv + argc);

	if(SDL_Init(SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) != 0)
	{
		std::cout << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
		return -1;
	}

//	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
//	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 16);

	if(TTF_Init() != 0)
	{
		std::cout << "Failed to initialize SDL_ttf: " << TTF_GetError() << std::endl;
		return -1;
	}

	TTF_Font *font = TTF_OpenFont("resources/ttf/MunroSmall.ttf", 10);
	if(!font)
	{
		std::cout << "Failed to load font: " << TTF_GetError() << std::endl;
		return -1;
	}

	DefaultSettingsProvider defaultSettingsProvider;
	SettingsProvider settingsProvider("settings.dat", &defaultSettingsProvider);
	SettingsHandler settingsHandler(&settingsProvider);
	Settings &settings = settingsHandler.settings();

	SoundHandler::setSoundVolume(settings.soundVolume() * 1.28f);
	SoundHandler::setMusicVolume(settings.musicVolume() * 1.28f);

	SDL_Window *window = SDL_CreateWindow("World²", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, settings.width(), settings.height(), SDL_WINDOW_OPENGL);
	assert(window);
	SDL_Renderer *sdlRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	assert(sdlRenderer);

	std::cout << "Loaded " << SDL_GameControllerAddMappingsFromFile("resources/gamecontrollerdb.txt") << " gamepad mappings" << std::endl;
	for (int i = 0; i < SDL_NumJoysticks(); i++)
	{
		if(SDL_IsGameController(i))
		{
			std::cout << "DEBUG: Opening gamepad " << SDL_GameControllerNameForIndex(i) << std::endl;
			SDL_GameControllerOpen(i);
		}
	}

	// Wrap the renderer in our own class to manage camera etc.
	Renderer renderer(sdlRenderer);
	MapSelectionToken mapSelectionToken(renderer, settingsHandler);
	StateHandler stateHandler(renderer, settingsHandler, mapSelectionToken);

	if(std::find(arguments.begin(), arguments.end(), "--nosplash") != arguments.end())
	{
		stateHandler.changeState<MainMenuState>(false);
	}
	else
	{
		stateHandler.changeState<SplashState>(false);
	}

	Ui::Label fpsLabel(5, 0, "", font, renderer);
	double lastFpsUpdate = 0;

	const uint64_t ticksPerSecond = SDL_GetPerformanceFrequency();
	bool debugText = false;
	uint64_t lastTicks = SDL_GetPerformanceCounter();
	for(bool shouldRun = true; shouldRun;)
	{
		const uint64_t currentTicks = SDL_GetPerformanceCounter();
		const double delta = (double)(currentTicks - lastTicks) / ticksPerSecond;
		lastTicks = currentTicks;

		SDL_Event event;

		while(SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
				{
					shouldRun = false;

					break;
				}

				case SDL_KEYDOWN:
				{
					stateHandler
						.currentState()
						.onKeyDown(event.key.keysym.sym);

					if (event.key.keysym.sym == SDLK_F11) // Jag har yakuake på F12
					{
						debugText = !debugText;
					}

					break;
				}

				case SDL_KEYUP:
				{
					stateHandler
						.currentState()
						.onKeyUp(event.key.keysym.sym);

					break;
				}

				case SDL_MOUSEBUTTONDOWN:
				{
					stateHandler
						.currentState()
						.onMouseButtonDown(event.button);

					break;
				}

				case SDL_MOUSEBUTTONUP:
				{
					stateHandler
						.currentState()
						.onMouseButtonUp(event.button);

					break;
				}

				case SDL_MOUSEMOTION:
				{
					stateHandler
						.currentState()
						.onMouseMove(event.motion);

					break;
				}

				case SDL_MOUSEWHEEL:
				{
					stateHandler
						.currentState()
						.onMouseWheel(event.wheel);

					break;
				}

				case SDL_CONTROLLERBUTTONDOWN:
				{
					stateHandler
						.currentState()
						.onControllerButtonDown(event.cbutton);

					break;
				}

				case SDL_CONTROLLERBUTTONUP:
				{
					stateHandler
						.currentState()
						.onControllerButtonUp(event.cbutton);

					break;
				}

				case SDL_CONTROLLERAXISMOTION:
				{
					stateHandler
						.currentState()
						.onControllerAxisMotion(event.caxis);

					break;
				}
			}
		}

		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);

		shouldRun &= stateHandler
			.currentState()
			.update(delta);

		stateHandler.draw(delta, renderer);

		// Clear camera before drawing UI
		renderer.setCamera(nullptr);

		if(debugText)
		{
			lastFpsUpdate += delta;
			if(lastFpsUpdate > 1)
			{
				const int fps = 1.0 / delta;
				fpsLabel.setText(std::to_string(fps).append(" FPS"));
				lastFpsUpdate = 0;
			}
			fpsLabel.draw(delta, renderer);
		}

		SDL_RenderPresent(renderer);
	}

	settingsHandler.save();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	TTF_Quit();
	SDL_Quit();
	return 0;
}
