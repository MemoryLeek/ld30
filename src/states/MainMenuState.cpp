#include <iostream>
#include <functional>

#include "MainMenuState.h"
#include "GameState.h"
#include "StateHandler.h"

MainMenuState::MainMenuState(StateHandler &stateHandler, Renderer &renderer)
	: MenuState(stateHandler, renderer)
{

}

std::vector<MenuItem> MainMenuState::items()
{
	return
	{
		MenuItem("Start", std::bind(&MainMenuState::start, this)),
		MenuItem("Exit", std::bind(&MenuState::exit, this))
	};
}

void MainMenuState::start()
{
	m_stateHandler.changeState<GameState>();
}
