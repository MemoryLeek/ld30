#include "LevelTile.h"

LevelTile::LevelTile()
	: m_id(0)
	, m_x(0)
	, m_y(0)
{

}

int LevelTile::id() const
{
	return m_id;
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
	stream >> tile.m_id;
	stream >> tile.m_x;
	stream >> tile.m_y;

	return stream;
}
