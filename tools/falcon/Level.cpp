#include <QBuffer>

#include "Level.h"

Level::Level(int width, int height, QImage tileset)
	: m_tileset(tileset)
	, m_width(width)
	, m_height(height)
{

}

void Level::addTile(LevelTile tile)
{
	m_tiles << tile;
}

QDataStream &operator <<(QDataStream &stream, const Level &level)
{
	QBuffer buffer;
	buffer.open(QIODevice::WriteOnly);

	QImage texture = level.m_tileset;
	texture.save(&buffer, "PNG");

	stream << buffer.data();
	stream << level.m_width;
	stream << level.m_height;
	stream << level.m_tiles;

	return stream;
}
