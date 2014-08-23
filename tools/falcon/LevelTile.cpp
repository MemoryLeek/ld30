#include "LevelTile.h"

LevelTile::LevelTile(int id, int x, int y)
	: m_id(id)
	, m_x(x)
	, m_y(y)
{

}

QDataStream &operator <<(QDataStream &stream, const LevelTile &tile)
{
	stream << tile.m_id;
	stream << tile.m_x;
	stream << tile.m_y;

	return stream;
}
