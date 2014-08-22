#include "SettingsMenuState.h"
#include "ResolutionMenuState.h"
#include "MainMenuState.h"
#include "StateHandler.h"

SettingsMenuState::SettingsMenuState(StateHandler &stateHandler, Renderer &renderer, SettingsHandler &settingsHandler)
	: MenuState(stateHandler, renderer, settingsHandler)
{

}

std::vector<MenuItem> SettingsMenuState::items()
{
	return
	{
		MenuItem("Resolution", std::bind(&SettingsMenuState::resolutionMenu, this))
	};
}

void SettingsMenuState::resolutionMenu()
{
	m_stateHandler.changeState<ResolutionMenuState>();
}

void SettingsMenuState::cancel()
{
	m_stateHandler.changeState<MainMenuState>();
}
