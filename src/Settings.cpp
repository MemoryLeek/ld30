#include "Settings.h"

Settings::Settings()
	: m_width(0)
	, m_height(0)
{

}

int Settings::width() const
{
	return m_width;
}

int Settings::height() const
{
	return m_height;
}

void Settings::setResolution(int width, int height)
{
	m_width = width;
	m_height = height;
}

BinaryStream &operator >>(BinaryStream &stream, Settings &settings)
{
	stream >> settings.m_width;
	stream >> settings.m_height;

	return stream;
}

BinaryStream &operator <<(BinaryStream &stream, const Settings &settings)
{
	stream << settings.m_width;
	stream << settings.m_height;

	return stream;
}
