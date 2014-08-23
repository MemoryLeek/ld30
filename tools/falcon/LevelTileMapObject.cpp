#include "LevelTileMapObject.h"

LevelTileMapObject::LevelTileMapObject(int id)
	: m_id(id)
{

}

QDataStream &operator <<(QDataStream &stream, const LevelTileMapObject &object)
{
	stream << object.m_id;

	return stream;
}
