#ifndef VICTORYSTATE_H
#define VICTORYSTATE_H

#include <SDL2/SDL_render.h>

#include "IState.h"

class StateHandler;
class SettingsHandler;
class Renderer;

class VictoryState : public IState
{
	public:
		VictoryState(StateHandler &stateHandler, Renderer &renderer, SettingsHandler &settingsHandler);

		bool update(double delta) override;

		void onKeyDown(SDL_Keycode keyCode) override;
		void onKeyUp(SDL_Keycode keyCode) override;
		void onMouseButtonDown(SDL_MouseButtonEvent event) override;
		void onMouseButtonUp(SDL_MouseButtonEvent event) override;
		void onMouseMove(SDL_MouseMotionEvent event) override;

	private:
		StateHandler &m_stateHandler;
		Renderer &m_renderer;

		SDL_Texture *m_gzTexture;
		SDL_Rect m_gzDest;

		SDL_Texture *m_timeTexture;
		SDL_Rect m_timeDest;
};

#endif // VICTORYSTATE_H
