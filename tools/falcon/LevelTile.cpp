#include "LevelTile.h"

LevelTile::LevelTile(int x, int y)
	: m_walkable(true)
	, m_x(x)
	, m_y(y)
{

}

void LevelTile::addLayer(LevelTileLayer layer)
{
	m_layers << layer;
}

void LevelTile::setWalkable(bool walkable)
{
	m_walkable = walkable;
}

void LevelTile::addMapObject(LevelTileMapObject object)
{
	m_objects << object;
}

QDataStream &operator <<(QDataStream &stream, const LevelTile &tile)
{
	stream << tile.m_layers;
	stream << tile.m_objects;
	stream << tile.m_walkable;
	stream << tile.m_x;
	stream << tile.m_y;

	return stream;
}
