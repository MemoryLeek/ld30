#include "LevelTileLayer.h"

LevelTileLayer::LevelTileLayer()
	: m_id(0)
{

}

int LevelTileLayer::id() const
{
	return m_id;
}

BinaryStream &operator >>(BinaryStream &stream, LevelTileLayer &layer)
{
	stream >> layer.m_id;

	return stream;
}
