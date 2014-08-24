#include <QBuffer>

#include "LevelBundle.h"

LevelBundle::LevelBundle()
{

}

void LevelBundle::setPreview(const QImage &preview)
{
	m_preview = preview;
}

void LevelBundle::setLevel1(Level *level1)
{
	m_level1 = level1;
}

void LevelBundle::setLevel2(Level *level2)
{
	m_level2 = level2;
}

QDataStream &operator <<(QDataStream &stream, const LevelBundle &bundle)
{
	QBuffer buffer;
	buffer.open(QIODevice::WriteOnly);

	QImage texture = bundle.m_preview;
	texture.save(&buffer, "PNG");

	stream << buffer.data();
	stream << *bundle.m_level1;
	stream << *bundle.m_level2;

	return stream;
}
