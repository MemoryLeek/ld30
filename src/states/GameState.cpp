#include <fstream>
#include <iostream>

#include <SDL2/SDL_image.h>

#include "GameState.h"
#include "Sprite.h"
#include "StateHandler.h"
#include "Renderer.h"

#include "drawables/Spawn.h"
#include "drawables/Goal.h"

GameState::GameState(StateHandler &stateHandler, Renderer &renderer, SettingsHandler &settingsHandler)
	: m_stateHandler(stateHandler)
	, m_renderer(renderer)
	, m_settingsHandler(settingsHandler)
	, m_level(renderer)
	, m_running(true)
{
	SDL_Surface *image = IMG_Load("resources/sprites/standing.png");
	// texture WILL LEAK, cba to properly free it for this simple test
	SDL_Texture *texture = SDL_CreateTextureFromSurface(m_renderer, image);
	SDL_FreeSurface(image);

	m_character = new Sprite(0, 0, 0, texture);

	std::fstream file("map.wld", std::ios::in | std::ios::binary);

	if (file.is_open())
	{
		BinaryStream stream(file);
		stream >> m_level;

		for (const LevelTile &tile : m_level.tiles())
		{
			for (const LevelTileMapObject &object : tile.objects())
			{
				switch (object.id())
				{
					case LevelTileMapObject::Spawn:
					{
						m_objects.push_back(new Spawn(tile.x() * TILE_SIZE, tile.y() * TILE_SIZE));

						break;
					}

					case LevelTileMapObject::Goal:
					{
						m_objects.push_back(new Goal(tile.x() * TILE_SIZE, tile.y() * TILE_SIZE));

						break;
					}
				}
			}
		}
	}

	m_pathfinder.reload(m_level);
}

GameState::~GameState()
{
}

bool GameState::update(double delta)
{
	// Create camera node 100px in front of character
	Node cameraNode(100, 0, 0, m_character);
	m_renderer.setCamera(&cameraNode);

	int width = 0;
	int height = 0;

	SDL_QueryTexture(m_level.tileset(), nullptr, nullptr, &width, &height);

	const int cx = m_renderer.cameraOffsetX();
	const int cy = m_renderer.cameraOffsetY();

	for (const LevelTile &tile : m_level.tiles())
	{
		const SDL_Rect target = { tile.x() * TILE_SIZE - TILE_SIZE / 2 - cx, tile.y() * TILE_SIZE - TILE_SIZE / 2 - cy, TILE_SIZE, TILE_SIZE };

		for (const LevelTileLayer &layer : tile.layers())
		{
			const int w = width / 32;
			const int y = layer.id() / w;
			const int x = layer.id() - (y * w);

			const SDL_Rect source = { x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE };

			SDL_RenderCopy(m_renderer, m_level.tileset(), &source, &target);
		}

		if (!tile.walkable())
		{
			SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
			SDL_RenderDrawRect(m_renderer, &target);
		}
	}

	for (IDrawable *drawable : m_objects)
	{
		drawable->draw(m_renderer);
	}

	// Rotate the character to verify that it actually works
//	m_character->setAngle(m_character->angle() + delta * 100);

	m_character->draw(m_renderer);

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
	}
}

void GameState::onKeyUp(SDL_Keycode keyCode)
{

}

void GameState::onMouseButtonDown(SDL_MouseButtonEvent event)
{

}

void GameState::onMouseButtonUp(SDL_MouseButtonEvent event)
{

}

void GameState::onMouseMove(SDL_MouseMotionEvent event)
{

}
