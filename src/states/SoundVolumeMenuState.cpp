#include <iostream>

#include "SettingsHandler.h"
#include "SettingsMenuState.h"
#include "SoundVolumeMenuState.h"
#include "StateHandler.h"
#include "SoundHandler.h"

SoundVolumeMenuState::SoundVolumeMenuState(StateHandler &stateHandler, Renderer &renderer, SettingsHandler &settingsHandler)
	: MenuState(stateHandler, renderer, settingsHandler)
{
}

std::vector<MenuItem> SoundVolumeMenuState::items()
{
	std::vector<MenuItem> items;

	const MenuItem item("Off", std::bind(&SoundVolumeMenuState::setVolume, this, 0));
	items.push_back(item);

	for (int i = 20; i <= 100; i += 20)
	{
		const std::string &title = std::to_string(i);
		const MenuItem item(title, std::bind(&SoundVolumeMenuState::setVolume, this, 128 * i / 100));

		items.push_back(item);
	}

	return items;
}

void SoundVolumeMenuState::setVolume(int volume)
{
	SoundHandler::setSoundVolume(volume);
	m_settingsHandler.settings().setSoundVolume(volume);
	m_stateHandler.changeState<SettingsMenuState>();
}
