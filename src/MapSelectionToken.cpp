#include <iostream>
#include "MapSelectionToken.h"

MapSelectionToken::MapSelectionToken(Renderer &renderer)
{
	m_items =
	{
		MapSelectionItem("Level 1", "resources/maps/level1.level", renderer),
		MapSelectionItem("Level 2", "resources/maps/level2.level", renderer)
	};
}

MapSelectionItem *MapSelectionToken::mapSelection() const
{
	return m_map;
}

void MapSelectionToken::setMapSelection(MapSelectionItem *map)
{
	std::cout << map << " " << &m_items[0] << std::endl;

	m_map = map;
}

std::vector<MapSelectionItem> &MapSelectionToken::items()
{
	return m_items;
}

Level &MapSelectionToken::level1()
{
	return m_map->level1();
}

Level &MapSelectionToken::level2()
{
	return m_map->level2();
}
