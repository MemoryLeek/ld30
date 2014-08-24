#ifndef ISTATE_H
#define ISTATE_H

#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_events.h>

class IState
{
	public:
		virtual ~IState() {}

		virtual bool update(double delta) = 0;

		virtual void onKeyDown(SDL_Keycode keyCode) = 0;
		virtual void onKeyUp(SDL_Keycode keyCode) = 0;
		virtual void onMouseButtonDown(SDL_MouseButtonEvent event) = 0;
		virtual void onMouseButtonUp(SDL_MouseButtonEvent event) = 0;
		virtual void onMouseMove(SDL_MouseMotionEvent event) = 0;
		virtual void onControllerButtonDown(SDL_ControllerButtonEvent event) = 0;
		virtual void onControllerButtonUp(SDL_ControllerButtonEvent event) = 0;
		virtual void onControllerAxisMotion(SDL_ControllerAxisEvent event) = 0;
};

#endif // ISTATE_H
