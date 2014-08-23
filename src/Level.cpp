#include "Level.h"
#include "drawables/Goal.h"
#include "drawables/Spawn.h"

Level::Level(Renderer &renderer)
	: m_tileset(renderer)
	, m_width(0)
	, m_height(0)
{

}

SDL_Texture *Level::tileset()
{
	return m_tileset;
}

int Level::width() const
{
	return m_width;
}

int Level::height() const
{
	return m_height;
}

std::vector<LevelTile> Level::tiles() const
{
	return m_tiles;
}

BinaryStream &operator >>(BinaryStream &stream, Level &level)
{
	stream >> level.m_tileset;
	stream >> level.m_width;
	stream >> level.m_height;
	stream >> level.m_tiles;

	return stream;
}
