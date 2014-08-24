#include <iostream>

#include <SDL2/SDL_image.h>

#include "MainMenuState.h"
#include "SplashState.h"
#include "StateHandler.h"
#include "Renderer.h"
#include "Util.h"

SplashState::SplashState(StateHandler &stateHandler, Renderer &renderer, SettingsHandler &settingsHandler)
	: m_stateHandler(stateHandler)
	, m_renderer(renderer)
	, m_splashTexture(nullptr)
	, m_totalTime(0)
	, m_skipped(false)
{
	UNUSED(settingsHandler);

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

bool SplashState::update(double delta)
{
	if(!m_splashTexture)
	{
		return true;
	}

	// Fade background from black to white
	int blackness = (m_totalTime > 0.2) ? 255 * (m_totalTime - 0.2) : 0;
	blackness = (blackness > 255) ? 255 : blackness;
	SDL_SetRenderDrawColor(m_renderer, blackness, blackness, blackness, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(m_renderer);
	SDL_RenderCopy(m_renderer, m_splashTexture, NULL, &m_destination);

	if ((m_totalTime += delta) > 2)
	{
		skip();
	}

	return true;
}

void SplashState::onKeyDown(SDL_Keycode keyCode)
{
	UNUSED(keyCode);

	skip();
}

void SplashState::onKeyUp(SDL_Keycode keyCode)
{
	UNUSED(keyCode);
}

void SplashState::onMouseButtonDown(SDL_MouseButtonEvent event)
{
	UNUSED(event);

	skip();
}

void SplashState::onMouseButtonUp(SDL_MouseButtonEvent event)
{
	UNUSED(event);
}

void SplashState::onMouseMove(SDL_MouseMotionEvent event)
{
	UNUSED(event);
}

void SplashState::onJoyButtonDown(SDL_JoyButtonEvent event)
{
	UNUSED(event);

	skip();
}

void SplashState::onJoyButtonUp(SDL_JoyButtonEvent event)
{
	UNUSED(event);
}

void SplashState::onJoyAxisMotion(SDL_JoyAxisEvent event)
{
	UNUSED(event);
}

void SplashState::skip()
{
	if (!m_skipped)
	{
		m_stateHandler.changeState<MainMenuState>(true);
		m_skipped = true;
	}
}
