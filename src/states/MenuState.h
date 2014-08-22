#ifndef MENUSTATE_H
#define MENUSTATE_H

#include <vector>

#include <SDL2/SDL_ttf.h>

#include "IState.h"
#include "MenuItem.h"

class StateHandler;
class Renderer;

class MenuState : public IState
{
	public:
		MenuState(StateHandler &stateHandler, Renderer &renderer);

		bool update(double delta) override;

		void onKeyDown(SDL_Keycode keyCode) override;
		void onKeyUp(SDL_Keycode keyCode) override;

		void exit();

	protected:
		virtual std::vector<MenuItem> items() = 0;

		virtual void cancel();

		StateHandler &m_stateHandler;
		Renderer &m_renderer;

	private:
		TTF_Font *m_font;

		int m_selectedIndex;
		int m_running;
};

#endif // MENUSTATE_H
