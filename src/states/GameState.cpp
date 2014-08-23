#include <fstream>
#include <iostream>

#include <SDL2/SDL_image.h>

#include "GameState.h"
#include "Player.h"
#include "Sprite.h"
#include "StateHandler.h"
#include "Renderer.h"

#include "drawables/Spawn.h"
#include "drawables/Goal.h"

GameState::GameState(StateHandler &stateHandler, Renderer &renderer, SettingsHandler &settingsHandler)
	: m_stateHandler(stateHandler)
	, m_renderer(renderer)
	, m_settingsHandler(settingsHandler)
	, m_level(&m_level1)
	, m_level1(renderer)
	, m_level2(renderer)
	, m_running(true)
{
	SDL_Surface *image = IMG_Load("resources/sprites/standing.png");
	// texture WILL LEAK, cba to properly free it for this simple test
	SDL_Texture *texture = SDL_CreateTextureFromSurface(m_renderer, image);
	SDL_FreeSurface(image);

	m_character = new Player(32, 32, texture);

	loadLevel("map.wld", m_level1);
	loadLevel("map2.wld", m_level2);
}

GameState::~GameState()
{
}

bool GameState::update(double delta)
{
	m_renderer.setCamera(m_character);

	if(m_mouseButtonDown)
	{
		const SDL_Point mouseWorld = {m_mousePosition.x + m_renderer.cameraOffsetX(), m_mousePosition.y + m_renderer.cameraOffsetY()};
		m_character->walkTowards(mouseWorld);
	}
	else
	{
		m_character->walkTowards({0, 0});
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

		if (!tile.walkable())
		{
			SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
			SDL_RenderDrawRect(m_renderer, &target);
		}

		for (IDrawable *drawable : tile.objects())
		{
			drawable->draw(delta, m_renderer);
		}
	}

	// Rotate the character to verify that it actually works
//	m_character->setAngle(m_character->angle() + delta * 100);

	m_character->draw(delta, m_renderer);

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
			if (m_level == &m_level1)
			{
				m_level = &m_level2;
			}
			else
			{
				m_level = &m_level1;
			}

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
