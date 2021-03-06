#ifndef MENUSTATE_H
#define MENUSTATE_H

#include <vector>

#include <SDL2/SDL_ttf.h>

#include "IState.h"
#include "MenuItem.h"

class StateHandler;
class Renderer;
class SettingsHandler;
class MapSelectionToken;

class MenuState : public IState
{
	public:
		MenuState(StateHandler &stateHandler, Renderer &renderer, SettingsHandler &settingsHandler, MapSelectionToken &mapSelectionToken);
		~MenuState();

		bool update(double delta) override;

		void onKeyDown(SDL_Keycode keyCode) override;
		void onKeyUp(SDL_Keycode keyCode) override;
		void onMouseButtonDown(SDL_MouseButtonEvent event) override;
		void onMouseButtonUp(SDL_MouseButtonEvent event) override;
		void onMouseMove(SDL_MouseMotionEvent event) override;
		void onMouseWheel(SDL_MouseWheelEvent event) override;
		void onControllerButtonDown(SDL_ControllerButtonEvent event) override;
		void onControllerButtonUp(SDL_ControllerButtonEvent event) override;
		void onControllerAxisMotion(SDL_ControllerAxisEvent event) override;

		void exit();

	protected:
		virtual std::vector<MenuItem> items() = 0;

		virtual void cancel();
		virtual void activate();

		StateHandler &m_stateHandler;
		Renderer &m_renderer;
		SettingsHandler &m_settingsHandler;
		MapSelectionToken &m_mapSelectionToken;

	private:
		void up();
		void down();

		TTF_Font *m_font;
		SDL_Texture *m_background;

		unsigned int m_selectedIndex;
		unsigned int m_mouseX;
		unsigned int m_mouseY;

		bool m_running;
		bool m_itemUnderCursor;
		bool m_joystickReady;
};

#endif // MENUSTATE_H
