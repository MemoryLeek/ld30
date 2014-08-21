#ifndef SPLASHSTATE_H
#define SPLASHSTATE_H

#include <SDL2/SDL_render.h>

#include "IState.h"

class SplashState : public IState
{
	public:
		SplashState(SDL_Renderer *renderer);
		~SplashState();

		IState *update(double delta) override;

	private:
		SDL_Renderer *const m_renderer;
		SDL_Texture *m_splashTexture;

		double m_totalTime;
		SDL_Rect m_destination;
};

#endif // SPLASHSTATE_H
