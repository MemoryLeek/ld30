#include <iostream>

#include "SettingsHandler.h"
#include "SettingsMenuState.h"
#include "MusicVolumeMenuState.h"
#include "StateHandler.h"
#include "SoundHandler.h"

MusicVolumeMenuState::MusicVolumeMenuState(StateHandler &stateHandler, Renderer &renderer, SettingsHandler &settingsHandler, MapSelectionToken &mapSelectionToken)
	: MenuState(stateHandler, renderer, settingsHandler, mapSelectionToken)
{
}

std::vector<MenuItem> MusicVolumeMenuState::items()
{
	std::vector<MenuItem> items;

	const MenuItem item("Off", std::bind(&MusicVolumeMenuState::setVolume, this, 0));
	items.push_back(item);

	for (int i = 20; i <= 100; i += 20)
	{
		const std::string &title = std::to_string(i);
		const MenuItem item(title, std::bind(&MusicVolumeMenuState::setVolume, this, 128 * i / 100));

		items.push_back(item);
	}

	return items;
}

void MusicVolumeMenuState::setVolume(int volume)
{
	SoundHandler::setMusicVolume(volume);

	m_settingsHandler.settings().setMusicVolume(volume);
	m_stateHandler.changeState<SettingsMenuState>(false);
}

void MusicVolumeMenuState::cancel()
{
	m_stateHandler.changeState<SettingsMenuState>(false);
}
