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
		virtual void onJoyButtonDown(SDL_JoyButtonEvent event) = 0;
		virtual void onJoyButtonUp(SDL_JoyButtonEvent event) = 0;
		virtual void onJoyAxisMotion(SDL_JoyAxisEvent event) = 0;
};

#endif // ISTATE_H
