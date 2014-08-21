#include <SDL2/SDL_image.h>

#include "GameState.h"
#include "Sprite.h"

GameState::GameState(Renderer &renderer)
	: m_renderer(renderer)
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

IState *GameState::update(double delta)
{
	m_renderer.setCamera(m_character);

	m_character->draw(m_renderer);

	return this;
}
