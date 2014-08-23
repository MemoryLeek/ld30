#include "LevelTile.h"

LevelTile::LevelTile()
	: m_walkable(true)
	, m_x(0)
	, m_y(0)
{

}

std::vector<LevelTileLayer> LevelTile::layers() const
{
	return m_layers;
}

std::vector<LevelTileMapObject> LevelTile::objects() const
{
	return m_objects;
}

bool LevelTile::walkable() const
{
	return m_walkable;
}

int LevelTile::x() const
{
	return m_x;
}

int LevelTile::y() const
{
	return m_y;
}

BinaryStream &operator >>(BinaryStream &stream, LevelTile &tile)
{
	stream >> tile.m_layers;
	stream >> tile.m_objects;
	stream >> tile.m_walkable;
	stream >> tile.m_x;
	stream >> tile.m_y;

	return stream;
}
