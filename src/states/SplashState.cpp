#include <iostream>

#include <SDL2/SDL_image.h>

#include "GameState.h"
#include "SplashState.h"

SplashState::SplashState(Renderer &renderer)
	: m_renderer(renderer)
	, m_splashTexture(nullptr)
	, m_totalTime(0)
{
	SDL_Surface *image = IMG_Load("resources/logo.png");
	if(!image)
	{
		std::cout << "Failed to load image: " << IMG_GetError << std::endl;
	}
	else
	{
		m_splashTexture = SDL_CreateTextureFromSurface(m_renderer, image);
		SDL_FreeSurface(image);
	}

	int textureWidth;
	int textureHeight;
	SDL_QueryTexture(m_splashTexture, nullptr, nullptr, &textureWidth, &textureHeight);

	m_destination.x = renderer.width() / 2 - textureWidth / 2;
	m_destination.y = renderer.height() / 2 - textureHeight / 2;
	m_destination.w = textureWidth;
	m_destination.h = textureHeight;
}

SplashState::~SplashState()
{
	SDL_DestroyTexture(m_splashTexture);
}

IState *SplashState::update(double delta)
{
	if(!m_splashTexture)
	{
		return this;
	}

	// Fade in texture over time
	const int alpha = (m_totalTime < 1) ? 255 * m_totalTime : 255;
	SDL_SetTextureAlphaMod(m_splashTexture, alpha);
	SDL_RenderCopy(m_renderer, m_splashTexture, NULL, &m_destination);

	m_totalTime += delta;
	if(m_totalTime > 2)
	{
		return new GameState(m_renderer);
	}

	return this;
}
