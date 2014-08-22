#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "MenuState.h"

class MainMenuState : public MenuState
{
	public:
		MainMenuState(StateHandler &stateHandler, Renderer &renderer);

		std::vector<MenuItem> items() override;

		void settingsMenu();

	private:
		void start();
};

#endif // MAINMENUSTATE_H
