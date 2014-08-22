#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SDL2/SDL_render.h>

#include "IState.h"

class Sprite;
class Renderer;
class StateHandler;

class GameState : public IState
{
	public:
		GameState(StateHandler &stateHandler, Renderer &renderer);
		~GameState();

		bool update(double delta) override;

		void onKeyDown(SDL_Keycode keyCode) override;
		void onKeyUp(SDL_Keycode keyCode) override;

	private:
		StateHandler &m_stateHandler;
		Renderer &m_renderer;

		Sprite *m_character;

		bool m_running;
};

#endif // SPLASHSTATE_H
