#ifndef SPLASHSTATE_H
#define SPLASHSTATE_H

#include <SDL2/SDL_render.h>

#include "IState.h"

class StateHandler;
class Renderer;

class SplashState : public IState
{
	public:
		SplashState(StateHandler &stateHandler, Renderer &renderer, SettingsHandler &settingsHandler, MapSelectionToken &mapSelectionToken);
		~SplashState();

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
		void skip();

		StateHandler &m_stateHandler;
		Renderer &m_renderer;
		SDL_Texture *m_splashTexture;

		double m_totalTime;

		bool m_skipped;

		SDL_Rect m_destination;
};

#endif // SPLASHSTATE_H
