#ifndef SOUNDVOLUMEMENUSTATE_H
#define SOUNDVOLUMEMENUSTATE_H

#include "MenuState.h"

class SoundVolumeMenuState : public MenuState
{
	public:
		SoundVolumeMenuState(StateHandler &stateHandler, Renderer &renderer, SettingsHandler &settingsHandler);

		std::vector<MenuItem> items() override;

	private:
		void setVolume(int volume);
};

#endif // SOUNDVOLUMEMENUSTATE_H
