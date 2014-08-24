#ifndef MAPSELECTIONTOKEN_H
#define MAPSELECTIONTOKEN_H

#include "MapSelectionItem.h"

class SettingsHandler;

class MapSelectionToken
{
	public:
		MapSelectionToken(Renderer &renderer, SettingsHandler &settingsHandler);

		void setMapSelection(MapSelectionItem *map);
		void markAsCleared();

		std::vector<MapSelectionItem> &items();

		Level &level1();
		Level &level2();

	private:
		std::vector<MapSelectionItem> m_items;

		SettingsHandler &m_settingsHandler;
		MapSelectionItem *m_map;
};

#endif // MAPSELECTIONTOKEN_H
