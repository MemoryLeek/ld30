#ifndef MAPSELECTIONTOKEN_H
#define MAPSELECTIONTOKEN_H

#include "MapSelectionItem.h"

class MapSelectionToken
{
	public:
		MapSelectionItem *mapSelection() const;
		void setMapSelection(MapSelectionItem *map);

	private:
		MapSelectionItem *m_map;
};

#endif // MAPSELECTIONTOKEN_H
