#ifndef SETTINGSMENUSTATE_H
#define SETTINGSMENUSTATE_H

#include "MenuState.h"

class SettingsMenuState : public MenuState
{
	public:
		SettingsMenuState(StateHandler &stateHandler, Renderer &renderer, SettingsHandler &settingsHandler);

		std::vector<MenuItem> items() override;

		void resolutionMenu();

	private:
		void cancel() override;
};

#endif // SETTINGSMENUSTATE_H
