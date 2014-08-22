#ifndef STATEHANDLER_H
#define STATEHANDLER_H

class Renderer;
class SettingsHandler;
class IState;

class StateHandler
{
	public:
		StateHandler(Renderer &renderer, SettingsHandler &settingsHandler);

		IState &currentState();

		template<class TState>
		void changeState()
		{
			delete m_currentState;

			m_currentState = new TState(*this, m_renderer, m_settingsHandler);
		}

	private:
		Renderer &m_renderer;
		SettingsHandler &m_settingsHandler;

		IState *m_currentState;
};

#endif // STATEHANDLER_H
