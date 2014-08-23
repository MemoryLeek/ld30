#include "LevelTileMapObject.h"

LevelTileMapObject::LevelTileMapObject()
	: m_id(0)
{

}

int LevelTileMapObject::id() const
{
	return m_id;
}

BinaryStream &operator >>(BinaryStream &stream, LevelTileMapObject &object)
{
	stream >> object.m_id;

	return stream;
}
