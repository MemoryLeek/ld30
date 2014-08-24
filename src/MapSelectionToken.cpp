#include <iostream>

#include "MapSelectionToken.h"
#include "SettingsHandler.h"

MapSelectionToken::MapSelectionToken(Renderer &renderer, SettingsHandler &settingsHandler)
	: m_settingsHandler(settingsHandler)
	, m_map(nullptr)
{
	m_items =
	{
		MapSelectionItem("Level 1", "resources/maps/level1.level", renderer),
		MapSelectionItem("Level 2", "resources/maps/level2.level", renderer)
	};
}

void MapSelectionToken::setMapSelection(MapSelectionItem *map)
{
	m_map = map;
}

void MapSelectionToken::markAsCleared()
{
	const unsigned int unlockedLevels = m_settingsHandler
		.settings()
		.unlockedLevels();

	for (unsigned int i = 0; i < m_items.size(); i++)
	{
		MapSelectionItem &map = m_items[i];

		if (i >= unlockedLevels && m_map == &map)
		{
			m_settingsHandler
				.settings()
				.setUnlockedLevels(i + 1);
		}
	}
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
