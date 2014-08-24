#include "LevelBundle.h"

LevelBundle::LevelBundle(Level &level1, Level &level2)
	: m_level1(level1)
	, m_level2(level2)
{

}

BinaryStream &operator >>(BinaryStream &stream, LevelBundle &bundle)
{
	stream >> bundle.m_preview;
	stream >> bundle.m_level1;
	stream >> bundle.m_level2;

	return stream;
}
