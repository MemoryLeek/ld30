#include "SettingsMenuState.h"
#include "ResolutionMenuState.h"
#include "SoundVolumeMenuState.h"
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
		MenuItem("Resolution", std::bind(&SettingsMenuState::resolutionMenu, this)),
		MenuItem("Sound Volume", std::bind(&SettingsMenuState::soundVolumeMenu, this))
	};
}

void SettingsMenuState::resolutionMenu()
{
	m_stateHandler.changeState<ResolutionMenuState>();
}

void SettingsMenuState::soundVolumeMenu()
{
	m_stateHandler.changeState<SoundVolumeMenuState>();
}

void SettingsMenuState::cancel()
{
	m_stateHandler.changeState<MainMenuState>();
}
