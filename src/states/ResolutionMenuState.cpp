#include <iostream>

#include "ResolutionMenuState.h"
#include "SettingsMenuState.h"
#include "StateHandler.h"
#include "SettingsHandler.h"
#include "StringEx.h"

ResolutionMenuState::ResolutionMenuState(StateHandler &stateHandler, Renderer &renderer, SettingsHandler &settingsHandler)
	: MenuState(stateHandler, renderer, settingsHandler)
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
	m_settingsHandler
		.settings()
		.setResolution(width, height);

	exit();
}

void ResolutionMenuState::cancel()
{
	m_stateHandler.changeState<SettingsMenuState>(false);
}
