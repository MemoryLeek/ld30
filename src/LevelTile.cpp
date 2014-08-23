#include "LevelTile.h"
#include "Util.h"

#include "drawables/Goal.h"
#include "drawables/Spawn.h"

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

std::vector<IDrawable *> LevelTile::objects() const
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
	std::vector<LevelTileMapObject> source;
	std::vector<IDrawable *> &target = tile.m_objects;

	stream >> tile.m_layers;
	stream >> source;
	stream >> tile.m_walkable;
	stream >> tile.m_x;
	stream >> tile.m_y;

	for (const LevelTileMapObject &object : source)
	{
		const int x = tile.m_x * TILE_SIZE;
		const int y = tile.m_y * TILE_SIZE;
		const int id = object.id();

		switch (id)
		{
			case LevelTileMapObject::Spawn:
			{
				target << new Spawn(x, y);

				break;
			}

			case LevelTileMapObject::Goal:
			{
				target << new Goal(x, y);

				break;
			}
		}
	}

	return stream;
}
