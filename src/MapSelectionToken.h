#ifndef MAPSELECTIONTOKEN_H
#define MAPSELECTIONTOKEN_H

#include "MapSelectionItem.h"

class MapSelectionToken
{
	public:
		MapSelectionToken(Renderer &renderer);

		MapSelectionItem *mapSelection() const;
		void setMapSelection(MapSelectionItem *map);

		std::vector<MapSelectionItem> &items();

		Level &level1();
		Level &level2();

	private:
		std::vector<MapSelectionItem> m_items;

		MapSelectionItem *m_map;
};

#endif // MAPSELECTIONTOKEN_H
