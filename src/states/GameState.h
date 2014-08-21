#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SDL2/SDL_render.h>

#include "IState.h"
#include "Renderer.h"

class Sprite;

class GameState : public IState
{
	public:
		GameState(Renderer &renderer);
		~GameState();

		IState *update(double delta) override;

	private:
		Renderer &m_renderer;

		Sprite *m_character;
};

#endif // SPLASHSTATE_H
