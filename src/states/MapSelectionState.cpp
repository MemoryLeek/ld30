#include "MapSelectionState.h"
#include "MapSelectionToken.h"
#include "StateHandler.h"
#include "GameState.h"
#include "Util.h"

MapSelectionState::MapSelectionState(StateHandler &stateHandler, Renderer &renderer, SettingsHandler &settingsHandler, MapSelectionToken &mapSelectionToken)
	: MenuState(stateHandler, renderer, settingsHandler, mapSelectionToken)
{
	m_items =
	{
		MapSelectionItem("Level 1", "resources/maps/map1_1.wld", "resources/maps/map1_2.wld"),
		MapSelectionItem("Level 2", "resources/maps/map2_1.wld", "resources/maps/map2_2.wld")
	};
}

std::vector<MenuItem> MapSelectionState::items()
{
	std::vector<MenuItem> items;

	for (const MapSelectionItem &map : m_items)
	{
		items << MenuItem(map.title(), std::bind(&MapSelectionState::selectMap, this, map));
	}

	return items;
}

void MapSelectionState::selectMap(MapSelectionItem &map)
{
	m_mapSelectionToken.setMapSelection(&map);
	m_stateHandler.changeState<GameState>(true);
}
