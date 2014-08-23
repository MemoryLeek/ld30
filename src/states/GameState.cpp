#include <fstream>
#include <iostream>

#include <SDL2/SDL_image.h>

#include "GameState.h"
#include "Sprite.h"
#include "StateHandler.h"
#include "Renderer.h"

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

	m_character = new Sprite(10, 20, 0, texture);

	std::fstream file("map.wld", std::ios::in | std::ios::binary);

	if (file.is_open())
	{
		BinaryStream stream(file);
		stream >> m_level;
	}
}

GameState::~GameState()
{
}

bool GameState::update(double delta)
{
	int width = 0;
	int height = 0;

	SDL_QueryTexture(m_level.tileset(), nullptr, nullptr, &width, &height);

	for (const LevelTile &tile : m_level.tiles())
	{
		const int w = width / 32;
		const int y = tile.id() / w;
		const int x = tile.id() - (y * w);

		SDL_Rect target = { tile.x() * TILE_SIZE, tile.y() * TILE_SIZE, TILE_SIZE, TILE_SIZE };
		SDL_Rect source = {x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE };

		SDL_RenderCopy(m_renderer, m_level.tileset(), &source, &target);
	}

	// Create camera node 100px in front of character
	Node cameraNode(100, 0, 0, m_character);
	m_renderer.setCamera(&cameraNode);

	// Rotate the character to verify that it actually works
	m_character->setAngle(m_character->angle() + delta * 100);

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
