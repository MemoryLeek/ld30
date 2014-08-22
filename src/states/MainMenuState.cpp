#include <iostream>
#include <functional>

#include "MainMenuState.h"
#include "GameState.h"
#include "SettingsMenuState.h"
#include "StateHandler.h"

MainMenuState::MainMenuState(StateHandler &stateHandler, Renderer &renderer, SettingsHandler &settingsHandler)
	: MenuState(stateHandler, renderer, settingsHandler)
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
	m_stateHandler.changeState<SettingsMenuState>();
}

void MainMenuState::cancel()
{
	exit();
}

void MainMenuState::start()
{
	m_stateHandler.changeState<GameState>();
}
