#include <SDL2/SDL_image.h>

#include "GameState.h"
#include "Sprite.h"
#include "StateHandler.h"
#include "Renderer.h"

GameState::GameState(StateHandler &stateHandler, Renderer &renderer)
	: m_stateHandler(stateHandler)
	, m_renderer(renderer)
	, m_running(true)
{
	SDL_Surface *image = IMG_Load("resources/sprites/standing.png");
	// texture WILL LEAK, cba to properly free it for this simple test
	SDL_Texture *texture = SDL_CreateTextureFromSurface(m_renderer, image);
	SDL_FreeSurface(image);

	m_character = new Sprite(10, 20, 0, texture);
}

GameState::~GameState()
{
}

bool GameState::update(double delta)
{
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
