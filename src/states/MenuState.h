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
		void onMouseButtonDown(SDL_MouseButtonEvent event) override;
		void onMouseButtonUp(SDL_MouseButtonEvent event) override;
		void onMouseMove(SDL_MouseMotionEvent event) override;

		void exit();

	protected:
		virtual std::vector<MenuItem> items() = 0;

		virtual void cancel();
		virtual void activate();

		StateHandler &m_stateHandler;
		Renderer &m_renderer;

	private:
		TTF_Font *m_font;

		int m_selectedIndex;
		int m_mouseX;
		int m_mouseY;

		bool m_running;
		bool m_itemUnderCursor;
};

#endif // MENUSTATE_H
