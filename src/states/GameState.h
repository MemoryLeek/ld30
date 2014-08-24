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
class Scoreboard;
class MapSelectionToken;

class GameState : public IState
{
	public:
		GameState(StateHandler &stateHandler, Renderer &renderer, SettingsHandler &settingsHandler, MapSelectionToken &mapSelectionToken);
		~GameState();

		bool update(double delta) override;

		void onKeyDown(SDL_Keycode keyCode) override;
		void onKeyUp(SDL_Keycode keyCode) override;
		void onMouseButtonDown(SDL_MouseButtonEvent event) override;
		void onMouseButtonUp(SDL_MouseButtonEvent event) override;
		void onMouseMove(SDL_MouseMotionEvent event) override;
		void onJoyButtonDown(SDL_JoyButtonEvent event) override;
		void onJoyButtonUp(SDL_JoyButtonEvent event) override;
		void onJoyAxisMotion(SDL_JoyAxisEvent event) override;

	private:
		void loadLevel(const std::string &fileName, Level &target);
		void switchLevels(Level &targetLevel, bool force = false);
		void drawLevel(Level &level, double delta);
		void respawn();
		void trySwitchLevels();

		StateHandler &m_stateHandler;
		Renderer &m_renderer;
		SettingsHandler &m_settingsHandler;

		Player *m_character;
		Scoreboard *m_scoreboard;

		float m_deathCamLifetime;
		float m_levelAlpha;
		float m_timeSinceStep;
		float m_timeSinceRespawn;
		float m_cameraScale;

		Level *m_currentLevel;
		Level *m_otherLevel;
		Level m_level1;
		Level m_level2;

		bool m_mouseButtonDown;
		bool m_running;
		bool m_levelSwitching;
		bool m_showScoreboard;
		bool m_skipped;

		SDL_Point m_mousePosition;
};

#endif // SPLASHSTATE_H
