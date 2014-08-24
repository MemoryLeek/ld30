#include <SDL2/SDL.h>

#include <iostream>

#include "StateHandler.h"
#include "Renderer.h"
#include "IState.h"

StateHandler::StateHandler(Renderer &renderer, SettingsHandler &settingsHandler, MapSelectionToken &mapSelectionToken)
	: m_renderer(renderer)
	, m_settingsHandler(settingsHandler)
	, m_mapSelectionToken(mapSelectionToken)
	, m_currentState(nullptr)
	, m_nextState(nullptr)
	, m_progress(0)
{

}

IState &StateHandler::currentState()
{
	return *m_currentState;
}

void StateHandler::draw(double delta, Renderer &renderer)
{
	if (m_progress > 0)
	{
		if ((m_progress -= delta * 1000) <= (TRANSITION_LENGTH / 2.0f))
		{
			if (m_nextState)
			{
				delete m_currentState;

				m_currentState = m_nextState;
				m_nextState = nullptr;
			}
		}

		const float progress = std::min(TRANSITION_LENGTH, m_progress) / TRANSITION_LENGTH;
		const float alpha = sin(progress * M_PI) * 255.0f;

		if (alpha >= 0)
		{
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, alpha);
			SDL_RenderFillRect(renderer, nullptr);
		}
	}
}
