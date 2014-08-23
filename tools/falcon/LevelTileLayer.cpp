#include "LevelTileLayer.h"

LevelTileLayer::LevelTileLayer(int id)
	: m_id(id)
{

}

int LevelTileLayer::id() const
{
	return m_id;
}

QDataStream &operator <<(QDataStream &stream, const LevelTileLayer &layer)
{
	stream << layer.m_id;

	return stream;
}
