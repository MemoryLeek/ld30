#ifndef STATEHANDLER_H
#define STATEHANDLER_H

class Renderer;
class IState;

class StateHandler
{
	public:
		StateHandler(Renderer &renderer);

		IState &currentState();

		template<class TState>
		void changeState()
		{
			delete m_currentState;

			m_currentState = new TState(*this, m_renderer);
		}

	private:
		Renderer &m_renderer;
		IState *m_currentState;
};

#endif // STATEHANDLER_H
