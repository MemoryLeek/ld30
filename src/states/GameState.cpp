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
	// Create camera node 100px in front of character
	Node cameraNode(100, 0, 0, m_character);
	m_renderer.setCamera(&cameraNode);

	// Rotate the character to verify that it actually works
	m_character->setAngle(m_character->angle() + delta * 100);

	m_character->draw(m_renderer);

	return this;
}
