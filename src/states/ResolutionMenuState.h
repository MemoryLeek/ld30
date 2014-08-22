#ifndef RESOLUTIONMENUSTATE_H
#define RESOLUTIONMENUSTATE_H

#include "MenuState.h"

class ResolutionMenuState : public MenuState
{
	public:
		ResolutionMenuState(StateHandler &stateHandler, Renderer &renderer);

		std::vector<MenuItem> items() override;

	private:
		void setResolution(int width, int height);
		void cancel() override;
};

#endif // RESOLUTIONMENUSTATE_H
