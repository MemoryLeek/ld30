#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <vector>

#include <SDL2/SDL_render.h>

#include "IState.h"
#include "Level.h"
#include "Pathfinder.h"

class Player;
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
		void loadLevel(const std::string &fileName, Level &target);

		StateHandler &m_stateHandler;
		Renderer &m_renderer;
		SettingsHandler &m_settingsHandler;
		Pathfinder m_pathfinder;

		Player *m_character;

		Level *m_level;
		Level m_level1;
		Level m_level2;

		bool m_mouseButtonDown;
		SDL_Point m_mousePosition;

		bool m_running;
};

#endif // SPLASHSTATE_H
