#include <math.h>
#include <fstream>
#include <iostream>

#include <SDL2/SDL_image.h>

#include "CollisionHandler.h"
#include "GameState.h"
#include "Player.h"
#include "Sprite.h"
#include "StateHandler.h"
#include "Renderer.h"
#include "SoundHandler.h"
#include "MainMenuState.h"
#include "MapSelectionToken.h"
#include "Util.h"

#include "drawables/Spawn.h"
#include "drawables/Goal.h"
#include "drawables/Scoreboard.h"

GameState::GameState(StateHandler &stateHandler, Renderer &renderer, SettingsHandler &settingsHandler, MapSelectionToken &mapSelectionToken)
	: m_stateHandler(stateHandler)
	, m_renderer(renderer)
	, m_settingsHandler(settingsHandler)
	, m_deathCamLifetime(0)
	, m_levelAlpha(255)
	, m_timeSinceStep(0)
	, m_timeSinceRespawn(0)
	, m_cameraScale(2)
	, m_currentLevel(&m_level1)
	, m_otherLevel(&m_level2)
	, m_level1()
	, m_level2()
	, m_mouseButtonDown(false)
	, m_running(true)
	, m_levelSwitching(false)
	, m_showScoreboard(false)
	, m_skipped(false)
{
	m_scoreboard = new Scoreboard(m_renderer);
	m_scoreboard->setTime(13.37f);

	m_character = new Player(13 * 32, 12 * 32, m_renderer);

	MapSelectionItem *map = mapSelectionToken.mapSelection();

	loadLevel(map->fileName1(), m_level1);
	loadLevel(map->fileName2(), m_level2);

	respawn();

	SoundHandler::playMusic(SoundHandler::Music::Ambient);
}

GameState::~GameState()
{
}

bool GameState::update(double delta)
{
	SDL_RenderSetScale(m_renderer, m_cameraScale, m_cameraScale);
	m_renderer.setCamera(m_character, m_cameraScale);

	if (m_levelSwitching)
	{
		if ((m_levelAlpha -= delta * 500) <= 0)
		{
			switchLevels(*m_otherLevel);
		}
	}

	if (m_deathCamLifetime > 0)
	{
		m_deathCamLifetime -= delta;
	}
	else if(m_character->isDead())
	{
		respawn();
	}

	if (!m_skipped &&
		!m_character->isDead() &&
		!m_showScoreboard)
	{
		// It's unhealthy to run while switching dimensions
		if(m_mouseButtonDown && !m_levelSwitching)
		{
			const SDL_Point mouseWorld = {m_mousePosition.x + m_renderer.cameraOffsetX(), m_mousePosition.y + m_renderer.cameraOffsetY()};

			m_character->walkTowards(mouseWorld);
			m_character->setIsWalking(true);

			if(m_timeSinceStep == 0 || m_timeSinceStep > 0.3)
			{
				SoundHandler::play((SoundHandler::Sound::Value)(SoundHandler::Sound::Step + rand() % 10));
				m_timeSinceStep = 0;
			}

			m_timeSinceStep += delta;
		}
		else
		{
			m_character->walkTowards({0, 0});
			m_character->setIsWalking(false);

			m_timeSinceStep = 0;
		}

		std::vector<Player*> movableObjects;
		movableObjects.push_back(m_character);
		CollisionHandler::resolveCollisions(movableObjects, m_currentLevel);
	}

	drawLevel(*m_otherLevel, delta);
	drawLevel(*m_currentLevel, delta);

	if (!m_character->isDead())
	{
		m_character->draw(delta * m_running, m_renderer);

		if (!m_showScoreboard)
		{
			m_timeSinceRespawn += delta;
		}
	}

	if (m_showScoreboard)
	{
		SDL_RenderSetScale(m_renderer, 1, 1);
		m_scoreboard->draw(delta, m_renderer);
	}

	if (!m_skipped && !m_running)
	{
		SoundHandler::stopMusic();

		m_stateHandler.changeState<MainMenuState>(true);
		m_skipped = true;

		return true;
	}

	return m_skipped || m_running;
}

void GameState::onKeyDown(SDL_Keycode keyCode)
{
	if (m_skipped)
	{
		return;
	}

	switch (keyCode)
	{
		case SDLK_ESCAPE:
		{
			m_running = false;

			break;
		}

		case SDLK_TAB:
		{
			trySwitchLevels();

			break;
		}

		case SDLK_RETURN:
		{
			if(m_showScoreboard)
			{
				respawn();
			}

			break;
		}
	}
}

void GameState::onKeyUp(SDL_Keycode keyCode)
{
	UNUSED(keyCode);
}

void GameState::onMouseButtonDown(SDL_MouseButtonEvent event)
{
	if (m_skipped)
	{
		return;
	}

	if (m_showScoreboard)
	{
		respawn();
	}

	m_mouseButtonDown = true;
	m_mousePosition = { event.x / int(m_cameraScale), event.y / int(m_cameraScale) };
}

void GameState::onMouseButtonUp(SDL_MouseButtonEvent event)
{
	m_mouseButtonDown = false;
	m_mousePosition = { event.x / int(m_cameraScale), event.y / int(m_cameraScale) };
}

void GameState::onMouseMove(SDL_MouseMotionEvent event)
{
	m_mousePosition = { event.x / int(m_cameraScale), event.y / int(m_cameraScale) };
}

void GameState::onControllerButtonDown(SDL_ControllerButtonEvent event)
{
	if (m_skipped)
	{
		return;
	}

	switch (event.button)
	{
		case Accept:
		{
			if (m_showScoreboard)
			{
				respawn();
			}
			else
			{
				trySwitchLevels();
			}

			break;
		}

		case Reject:
		{
			m_running = false;

			break;
		}
	}
}

void GameState::onControllerButtonUp(SDL_ControllerButtonEvent event)
{
	UNUSED(event);
}

void GameState::onControllerAxisMotion(SDL_ControllerAxisEvent event)
{
	if (m_skipped)
	{
		return;
	}

	event.value = (abs(event.value) > 6000) ? event.value : 0;

	switch (event.axis)
	{
		case Horizontal:
		{
			m_mousePosition.x = (m_character->x() + event.value) * (event.value != 0);
			m_mouseButtonDown = m_mousePosition.x || m_mousePosition.y;

			break;
		}

		case Vertical:
		{
			m_mousePosition.y = (m_character->y() + event.value) * (event.value != 0);
			m_mouseButtonDown = m_mousePosition.x || m_mousePosition.y;

			break;
		}
	}
}

void GameState::loadLevel(const std::string &fileName, Level &target)
{
	std::fstream file(fileName, std::ios::in | std::ios::binary);

	if (file.is_open())
	{
		BinaryStream stream(file, &m_renderer);
		stream >> target;
	}
}

void GameState::switchLevels(Level &targetLevel, bool force)
{
	if(m_character->isDead() && !force)
	{
		return; // You're not going anywhere
	}

	m_otherLevel = m_currentLevel;
	m_currentLevel = &targetLevel;

	m_levelSwitching = false;
	m_levelAlpha = 255;

	if(CollisionHandler::isPlayerInWall(*m_character, *m_currentLevel))
	{
		m_deathCamLifetime = 3;
		SoundHandler::play(SoundHandler::Sound::Squish);
		m_character->kill();
	}
}

void GameState::drawLevel(Level &level, double delta)
{
	int width = 0;
	int height = 0;

	SDL_Texture *tileset = level.tileset();
	SDL_QueryTexture(tileset, nullptr, nullptr, &width, &height);

	m_cameraScale = sin((m_levelAlpha / 255.0f) * M_PI) * 20 + 2;

	const int cx = m_renderer.cameraOffsetX();
	const int cy = m_renderer.cameraOffsetY();

	for (const LevelTile &tile : level.tiles())
	{
		for (const LevelTileLayer &layer : tile.layers())
		{
			const int w = width / 32;
			const int y = layer.id() / w;
			const int x = layer.id() - (y * w);
			const int s = TILE_SIZE;

			SDL_Rect target = { tile.x() * s - s / 2 - cx, tile.y() * s - s / 2 - cy, s, s };
			SDL_Rect source = { x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE };

			SDL_SetTextureAlphaMod(tileset, &level == m_otherLevel ? 255.0 - m_levelAlpha : m_levelAlpha);
			SDL_RenderCopy(m_renderer, tileset, &source, &target);
		}
	}

	for (const LevelTile &tile : level.tiles())
	{
		for (IDrawable *drawable : tile.objects())
		{
			drawable->draw(delta, m_renderer);

			if (&level == m_currentLevel)
			{
				Goal *goal = dynamic_cast<Goal *>(drawable);

				if (goal && !m_showScoreboard)
				{
					if (tile.x() == floor((m_character->x() + (TILE_SIZE / 2)) / TILE_SIZE) &&
						tile.y() == floor((m_character->y() + (TILE_SIZE / 2)) / TILE_SIZE))
					{
						m_character->walkTowards({ 0, 0 }); // Stop running around!
						m_scoreboard->setTime(m_timeSinceRespawn);
						m_showScoreboard = true;
					}
				}
			}
		}
	}
}

void GameState::respawn()
{
	if(m_currentLevel != &m_level1)
	{
		switchLevels(m_level1, true);
	}

	const Spawn *spawn = m_currentLevel->findTile<Spawn>();

	if(spawn)
	{
		m_character->respawn(spawn->x(), spawn->y());
		m_timeSinceRespawn = 0;
		m_showScoreboard = false;
	}
}

void GameState::trySwitchLevels()
{
	if (!m_character->isDead() &&
		!m_levelSwitching)
	{
		m_levelSwitching = true;

		SoundHandler::play(SoundHandler::Sound::WorldSwitch);
	}
}
