#include <sstream>

#include <SDL2/SDL_ttf.h>

#include "VictoryState.h"
#include "StateHandler.h"
#include "Renderer.h"
#include "GlobalDataStorage.h"

VictoryState::VictoryState(StateHandler &stateHandler, Renderer &renderer, SettingsHandler &settingsHandler)
	: m_stateHandler(stateHandler)
	, m_renderer(renderer)
	, m_gzTexture(nullptr)
{
	TTF_Font *font = TTF_OpenFont("resources/ttf/Oxygen-Regular.ttf", 48);

	SDL_Surface *surface = TTF_RenderText_Blended(font, "Congratulations!", {0, 255, 0, SDL_ALPHA_OPAQUE});
	m_gzTexture = SDL_CreateTextureFromSurface(m_renderer, surface);
	SDL_FreeSurface(surface);

	std::ostringstream time;
	time << GlobalDataStorage::levelCompletionTime() << " seconds";
	surface = TTF_RenderText_Blended(font, time.str().c_str(), {0, 255, 0, SDL_ALPHA_OPAQUE});
	m_timeTexture = SDL_CreateTextureFromSurface(m_renderer, surface);
	SDL_FreeSurface(surface);

	TTF_CloseFont(font);

	SDL_QueryTexture(m_gzTexture, nullptr, nullptr, &m_gzDest.w, &m_gzDest.h);
	m_gzDest.x = m_renderer.width() / 2 - m_gzDest.w / 2;
	m_gzDest.y = m_renderer.height() / 2 - m_gzDest.h;

	SDL_QueryTexture(m_timeTexture, nullptr, nullptr, &m_timeDest.w, &m_timeDest.h);
	m_timeDest.x = m_renderer.width() / 2 - m_timeDest.w / 2;
	m_timeDest.y = m_renderer.height() / 2;
}

bool VictoryState::update(double delta)
{
	m_renderer.setCamera(nullptr);
	SDL_RenderCopy(m_renderer, m_gzTexture, nullptr, &m_gzDest);
	SDL_RenderCopy(m_renderer, m_timeTexture, nullptr, &m_timeDest);
	return true;
}

void VictoryState::onKeyDown(SDL_Keycode keyCode)
{

}

void VictoryState::onKeyUp(SDL_Keycode keyCode)
{

}

void VictoryState::onMouseButtonDown(SDL_MouseButtonEvent event)
{

}

void VictoryState::onMouseButtonUp(SDL_MouseButtonEvent event)
{

}

void VictoryState::onMouseMove(SDL_MouseMotionEvent event)
{

}
