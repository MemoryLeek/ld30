#ifndef SPLASHSTATE_H
#define SPLASHSTATE_H

#include <SDL2/SDL_render.h>

#include "IState.h"
#include "Renderer.h"

class SplashState : public IState
{
	public:
		SplashState(Renderer &renderer);
		~SplashState();

		IState *update(double delta) override;

	private:
		Renderer &m_renderer;
		SDL_Texture *m_splashTexture;

		double m_totalTime;
		SDL_Rect m_destination;
};

#endif // SPLASHSTATE_H
