#include <iostream>
#include <functional>

#include "MainMenuState.h"
#include "SettingsMenuState.h"
#include "StateHandler.h"
#include "MapSelectionState.h"

MainMenuState::MainMenuState(StateHandler &stateHandler, Renderer &renderer, SettingsHandler &settingsHandler, MapSelectionToken &mapSelectionToken)
	: MenuState(stateHandler, renderer, settingsHandler, mapSelectionToken)
{

}

std::vector<MenuItem> MainMenuState::items()
{
	return
	{
		MenuItem("Start", std::bind(&MainMenuState::start, this)),
		MenuItem("Settings", std::bind(&MainMenuState::settingsMenu, this)),
		MenuItem("Exit", std::bind(&MenuState::exit, this))
	};
}

void MainMenuState::settingsMenu()
{
	m_stateHandler.changeState<SettingsMenuState>(false);
}

void MainMenuState::cancel()
{
	exit();
}

void MainMenuState::start()
{
	m_stateHandler.changeState<MapSelectionState>(false);
}
