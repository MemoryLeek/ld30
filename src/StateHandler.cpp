#include "StateHandler.h"

StateHandler::StateHandler(Renderer &renderer, SettingsHandler &settingsHandler)
	: m_renderer(renderer)
	, m_settingsHandler(settingsHandler)
	, m_currentState(0)
{

}

IState &StateHandler::currentState()
{
	return *m_currentState;
}
