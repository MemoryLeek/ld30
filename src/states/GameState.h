#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <vector>

#include <SDL2/SDL_render.h>

#include "IState.h"
#include "Level.h"

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
		void switchLevels(Level &targetLevel, bool force = false);
		void drawLevel(Level &level, double delta);

		StateHandler &m_stateHandler;
		Renderer &m_renderer;
		SettingsHandler &m_settingsHandler;

		Player *m_character;

		float m_deathCamLifetime;
		float m_levelAlpha;

		float m_timeSinceStep;
		float m_timeSinceRespawn;
		Level *m_currentLevel;
		Level *m_otherLevel;

		Level m_level1;
		Level m_level2;

		bool m_mouseButtonDown;
		bool m_running;
		bool m_levelSwitching;

		float m_cameraScale;
		SDL_Point m_mousePosition;
};

#endif // SPLASHSTATE_H
