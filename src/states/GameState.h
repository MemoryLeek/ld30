#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SDL2/SDL_render.h>

#include "IState.h"

class Sprite;

class GameState : public IState
{
	public:
		GameState(SDL_Renderer *renderer);
		~GameState();

		IState *update(double delta) override;

	private:
		SDL_Renderer *const m_renderer;

		Sprite *m_character;
};

#endif // SPLASHSTATE_H
