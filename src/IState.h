#ifndef ISTATE_H
#define ISTATE_H

#include "SDL2/SDL_keycode.h"

class IState
{
	public:
		virtual ~IState() {}

		virtual bool update(double delta) = 0;

		virtual void onKeyDown(SDL_Keycode keyCode) = 0;
		virtual void onKeyUp(SDL_Keycode keyCode) = 0;
};

#endif // ISTATE_H
