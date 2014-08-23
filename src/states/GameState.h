#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <vector>

#include <SDL2/SDL_render.h>

#include "IState.h"
#include "Level.h"
#include "Pathfinder.h"

class Sprite;
class Renderer;
class StateHandler;
class SettingsHandler;
class IDrawable;

class GameState : public IState
{
	public:
		GameState(StateHandler &stateHandler, Renderer &renderer, SettingsHandler &settingsHandler);
		~GameState();

		bool update(double delta) override;

		void onKeyDown(SDL_Keycode keyCode) override;
		void onKeyUp(SDL_Keycode keyCode) override;
		void onMouseButtonDown(SDL_MouseButtonEvent event) override;
		void onMouseButtonUp(SDL_MouseButtonEvent event) override;
		void onMouseMove(SDL_MouseMotionEvent event) override;

	private:
		std::vector<IDrawable *> m_objects;

		StateHandler &m_stateHandler;
		Renderer &m_renderer;
		SettingsHandler &m_settingsHandler;

		Sprite *m_character;
		Level m_level;
		Pathfinder m_pathfinder;

		bool m_running;
};

#endif // SPLASHSTATE_H
