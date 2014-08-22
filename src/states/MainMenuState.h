#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "MenuState.h"

class MainMenuState : public MenuState
{
	public:
		MainMenuState(StateHandler &stateHandler, Renderer &renderer, SettingsHandler &settingsHandler);

		std::vector<MenuItem> items() override;

		void settingsMenu();

	private:
		void cancel() override;
		void start();
};

#endif // MAINMENUSTATE_H
