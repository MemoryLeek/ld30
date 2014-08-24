#include "MapSelectionToken.h"

MapSelectionItem *MapSelectionToken::mapSelection() const
{
	return m_map;
}

void MapSelectionToken::setMapSelection(MapSelectionItem *map)
{
	m_map = map;
}
