#ifndef SOUNDVOLUMEMENUSTATE_H
#define SOUNDVOLUMEMENUSTATE_H

#include "MenuState.h"

class SoundVolumeMenuState : public MenuState
{
	public:
		SoundVolumeMenuState(StateHandler &stateHandler, Renderer &renderer, SettingsHandler &settingsHandler, MapSelectionToken &mapSelectionToken);

		std::vector<MenuItem> items() override;

	private:
		void setVolume(int volume);
		void cancel() override;
};

#endif // SOUNDVOLUMEMENUSTATE_H
