#include <iostream>

#include "ResolutionMenuState.h"
#include "SettingsMenuState.h"
#include "StateHandler.h"
#include "StringEx.h"

ResolutionMenuState::ResolutionMenuState(StateHandler &stateHandler, Renderer &renderer)
	: MenuState(stateHandler, renderer)
{

}

std::vector<MenuItem> ResolutionMenuState::items()
{
	std::vector<MenuItem> items;

	for (int i = 0; i < SDL_GetNumDisplayModes(0); i++)
	{
		SDL_DisplayMode mode;
		SDL_GetDisplayMode(0, i, &mode);

		const std::string &title = StringEx::format("%1x%2", mode.w, mode.h);
		const MenuItem item(title, std::bind(&ResolutionMenuState::setResolution, this, mode.w, mode.h));

		items.push_back(item);
	}

	return items;
}

void ResolutionMenuState::setResolution(int width, int height)
{
	// Do stuff here, like, save the resolution and such

	std::cout << "This would have selected the resolution " << StringEx::format("%1x%2", width, height) << std::endl;

	exit();
}

void ResolutionMenuState::cancel()
{
	m_stateHandler.changeState<SettingsMenuState>();
}
