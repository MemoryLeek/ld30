#include "Settings.h"

Settings::Settings()
	: m_width(0)
	, m_height(0)
	, m_lastSelectedLevel(0)
	, m_unlockedLevels(0)
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
	return m_soundVolume;
}

int Settings::musicVolume() const
{
	return m_musicVolume;
}

int Settings::lastSelectedLevel() const
{
	return m_lastSelectedLevel;
}

int Settings::unlockedLevels() const
{
	return m_unlockedLevels;
}

void Settings::setResolution(int width, int height)
{
	m_width = width;
	m_height = height;
}

void Settings::setSoundVolume(int volume)
{
	m_soundVolume = volume;
}

void Settings::setMusicVolume(int volume)
{
	m_musicVolume = volume;
}

void Settings::setLastSelectedLevel(int lastSelectedLevel)
{
	m_lastSelectedLevel = lastSelectedLevel;
}

void Settings::setUnlockedLevels(int unlockedLevels)
{
	m_unlockedLevels = unlockedLevels;
}

BinaryStream &operator >>(BinaryStream &stream, Settings &settings)
{
	stream >> settings.m_width;
	stream >> settings.m_height;
	stream >> settings.m_soundVolume;
	stream >> settings.m_musicVolume;
	stream >> settings.m_lastSelectedLevel;
	stream >> settings.m_unlockedLevels;

	return stream;
}

BinaryStream &operator <<(BinaryStream &stream, const Settings &settings)
{
	stream << settings.m_width;
	stream << settings.m_height;
	stream << settings.m_soundVolume;
	stream << settings.m_musicVolume;
	stream << settings.m_lastSelectedLevel;
	stream << settings.m_unlockedLevels;

	return stream;
}
