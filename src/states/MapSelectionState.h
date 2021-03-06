#ifndef MAPSELECTIONSTATE_H
#define MAPSELECTIONSTATE_H

#include <SDL2/SDL_ttf.h>

#include <vector>

#include "IState.h"
#include "MapSelectionItem.h"

class StateHandler;
class Renderer;
class SettingsHandler;
class MapSelectionToken;

class MapSelectionState : public IState
{
	const int ITEM_WIDTH = 270;
	const int ITEM_HEIGHT = 206;

	public:
		MapSelectionState(StateHandler &stateHandler, Renderer &renderer, SettingsHandler &settingsHandler, MapSelectionToken &mapSelectionToken);
		~MapSelectionState();

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

	private:
		void left();
		void right();
		void activate();
		void cancel();

		StateHandler &m_stateHandler;
		Renderer &m_renderer;
		SettingsHandler &m_settingsHandler;
		MapSelectionToken &m_mapSelectionToken;

		TTF_Font *m_mainFont;
		TTF_Font *m_subFont;

		SDL_Texture *m_background;

		unsigned int m_selectedMap;

		bool m_joystickReady;
		bool m_itemUnderCursor;
		bool m_skipped;
		bool m_adjustSoundVolume;
		bool m_adjustMusicVolume;
		bool m_running;
};

#endif // MAPSELECTIONSTATE_H
