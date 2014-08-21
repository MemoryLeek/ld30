#include "GameState.h"

GameState::GameState(SDL_Renderer *renderer)
	: m_renderer(renderer)
{
}

GameState::~GameState()
{
}

IState *GameState::update(double delta)
{
	return this;
}
