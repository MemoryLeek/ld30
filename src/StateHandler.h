#ifndef STATEHANDLER_H
#define STATEHANDLER_H

#include "IDrawable.h"

class Renderer;
class SettingsHandler;
class MapSelectionToken;
class IState;

class StateHandler : public IDrawable
{
	const float TRANSITION_LENGTH = 1000;

	public:
		StateHandler(Renderer &renderer, SettingsHandler &settingsHandler, MapSelectionToken &mapSelectionToken);

		IState &currentState();

		template<class TState>
		void changeState(bool transition)
		{
			if (transition)
			{
				m_nextState = new TState(*this, m_renderer, m_settingsHandler, m_mapSelectionToken);
				m_progress = TRANSITION_LENGTH;
			}
			else
			{
				delete m_currentState;

				m_currentState = new TState(*this, m_renderer, m_settingsHandler, m_mapSelectionToken);
			}
		}

		void draw(double delta, Renderer &renderer) override;

	private:
		Renderer &m_renderer;
		SettingsHandler &m_settingsHandler;
		MapSelectionToken &m_mapSelectionToken;

		IState *m_currentState;
		IState *m_nextState;

		float m_progress;
};

#endif // STATEHANDLER_H
