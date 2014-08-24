#ifndef MUSICVOLUMEMENUSTATE_H
#define MUSICVOLUMEMENUSTATE_H

#include "MenuState.h"

class MusicVolumeMenuState : public MenuState
{
	public:
		MusicVolumeMenuState(StateHandler &stateHandler, Renderer &renderer, SettingsHandler &settingsHandler);

		std::vector<MenuItem> items() override;

	private:
		void setVolume(int volume);
};

#endif // MUSICVOLUMEMENUSTATE_H
