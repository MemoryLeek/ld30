#ifndef MAPSELECTIONSTATE_H
#define MAPSELECTIONSTATE_H

#include <vector>

#include "MenuState.h"
#include "MapSelectionItem.h"

class MapSelectionState : public MenuState
{
	public:
		MapSelectionState(StateHandler &stateHandler, Renderer &renderer, SettingsHandler &settingsHandler, MapSelectionToken &mapSelectionToken);

		std::vector<MenuItem> items() override;

	private:
		void selectMap(MapSelectionItem &map);
		void cancel() override;

		std::vector<MapSelectionItem> m_items;
};

#endif // MAPSELECTIONSTATE_H
