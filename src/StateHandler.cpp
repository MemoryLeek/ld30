#include "StateHandler.h"

StateHandler::StateHandler(Renderer &renderer)
	: m_renderer(renderer)
	, m_currentState(0)
{

}

IState &StateHandler::currentState()
{
	return *m_currentState;
}
