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

int Settings::soundVolume() const
{
	return m_volume;
}

void Settings::setResolution(int width, int height)
{
	m_width = width;
	m_height = height;
}

void Settings::setSoundVolume(int volume)
{
	m_volume = volume;
}

BinaryStream &operator >>(BinaryStream &stream, Settings &settings)
{
	stream >> settings.m_width;
	stream >> settings.m_height;
	stream >> settings.m_volume;

	return stream;
}

BinaryStream &operator <<(BinaryStream &stream, const Settings &settings)
{
	stream << settings.m_width;
	stream << settings.m_height;
	stream << settings.m_volume;

	return stream;
}
