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

#include "drawables/Spawn.h"
#include "drawables/Goal.h"

GameState::GameState(StateHandler &stateHandler, Renderer &renderer, SettingsHandler &settingsHandler)
	: m_stateHandler(stateHandler)
	, m_renderer(renderer)
	, m_settingsHandler(settingsHandler)
	, m_level(&m_level1)
	, m_level1(renderer)
	, m_level2(renderer)
	, m_mouseButtonDown(false)
	, m_running(true)
{
	SDL_Surface *image = IMG_Load("resources/sprites/standing.png");
	// texture WILL LEAK, cba to properly free it for this simple test
	SDL_Texture *texture = SDL_CreateTextureFromSurface(m_renderer, image);
	SDL_FreeSurface(image);

	loadLevel("map.wld", m_level1);
	loadLevel("map2.wld", m_level2);

	m_character = new Player(0, 0, texture);
	moveToSpawn(m_character, m_level);

	SDL_assert(m_character);
}

GameState::~GameState()
{
}

bool GameState::update(double delta)
{
	m_renderer.setCamera(m_character);

	if(m_deathCamLifetime > 0)
	{
		m_deathCamLifetime -= delta;
	}
	else if(m_character->isDead())
	{
		m_level = &m_level1;
		const Spawn *spawn = m_level->findTile<Spawn>();
		if(spawn)
		{
			m_character->respawn(spawn->x(), spawn->y());
		}
	}

	if(!m_character->isDead())
	{
		if(m_mouseButtonDown)
		{
			const SDL_Point mouseWorld = {m_mousePosition.x + m_renderer.cameraOffsetX(), m_mousePosition.y + m_renderer.cameraOffsetY()};
			m_character->walkTowards(mouseWorld);

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
			m_timeSinceStep = 0;
		}

		std::vector<Player*> movableObjects;
		movableObjects.push_back(m_character);
		CollisionHandler::resolveCollisions(movableObjects, m_level);

		const Goal *goal = m_level->findTile<Goal>();
		if(goal && ((int)m_character->x() + (TILE_SIZE / 2)) / TILE_SIZE == goal->tileX() && ((int)m_character->y() + (TILE_SIZE / 2)) / TILE_SIZE == goal->tileY())
		{
			std::cout << "Wow man, you made it to ze goal!" << std::endl;
		}
	}

	int width = 0;
	int height = 0;

	SDL_QueryTexture(m_level->tileset(), nullptr, nullptr, &width, &height);

	const int cx = m_renderer.cameraOffsetX();
	const int cy = m_renderer.cameraOffsetY();

	for (const LevelTile &tile : m_level->tiles())
	{
		const SDL_Rect target = { tile.x() * TILE_SIZE - TILE_SIZE / 2 - cx, tile.y() * TILE_SIZE - TILE_SIZE / 2 - cy, TILE_SIZE, TILE_SIZE };

		for (const LevelTileLayer &layer : tile.layers())
		{
			const int w = width / 32;
			const int y = layer.id() / w;
			const int x = layer.id() - (y * w);

			const SDL_Rect source = { x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE };

			SDL_RenderCopy(m_renderer, m_level->tileset(), &source, &target);
		}

//		if (!tile.walkable())
//		{
//			SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
//			SDL_RenderDrawRect(m_renderer, &target);
//		}

		for (IDrawable *drawable : tile.objects())
		{
			drawable->draw(delta, m_renderer);
		}
	}

	if(!m_character->isDead())
	{
		m_character->draw(delta, m_renderer);
	}

	return m_running;
}

void GameState::onKeyDown(SDL_Keycode keyCode)
{
	switch (keyCode)
	{
		case SDLK_ESCAPE:
		{
			m_running = false;

			break;
		}

		case SDLK_TAB:
		{
			switchLevels();

			break;
		}
	}
}

void GameState::onKeyUp(SDL_Keycode keyCode)
{

}

void GameState::onMouseButtonDown(SDL_MouseButtonEvent event)
{
	m_mouseButtonDown = true;
	m_mousePosition = {event.x, event.y};
}

void GameState::onMouseButtonUp(SDL_MouseButtonEvent event)
{
	m_mouseButtonDown = false;
	m_mousePosition = {event.x, event.y};
}

void GameState::onMouseMove(SDL_MouseMotionEvent event)
{
	m_mousePosition = {event.x, event.y};
}

void GameState::loadLevel(const std::string &fileName, Level &target)
{
	std::fstream file(fileName, std::ios::in | std::ios::binary);

	if (file.is_open())
	{
		BinaryStream stream(file);
		stream >> target;
	}
}

void GameState::switchLevels()
{
	if(m_character->isDead())
	{
		return; // You're not going anywhere
	}

	SoundHandler::play(SoundHandler::Sound::WorldSwitch);
	if (m_level == &m_level1)
	{
		m_level = &m_level2;
	}
	else
	{
		m_level = &m_level1;
	}

	// It's unhealthy to run while switching dimensions
	m_mouseButtonDown = false;

	if(CollisionHandler::isPlayerInWall(*m_character, *m_level))
	{
		std::cout << "Dayyym, you dead." << std::endl;
		m_deathCamLifetime = 3;
		SoundHandler::play(SoundHandler::Sound::Squish);
		m_character->kill();
	}
}

void GameState::moveToSpawn(Player *player, Level *level)
{
	const Spawn *spawn = m_level->findTile<Spawn>();
	if(spawn)
	{
		const int x = spawn->x();
		const int y = spawn->y();
		m_character->setPosition(x, y);
	}
}
