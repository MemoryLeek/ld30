#include <iostream>

#include "Settings.h"
#include "Util.h"

Settings::Settings()
	: m_width(0)
	, m_height(0)
	, m_lastSelectedLevel(0)
	, m_soundVolume(100)
	, m_musicVolume(100)
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
	return m_levelCompletionTimes.size();
}

bool Settings::isLevelUnlocked(unsigned int index) const
{
	return m_levelCompletionTimes.size() >= index;
}

bool Settings::isLevelCompleted(unsigned int index) const
{
	return m_levelCompletionTimes.size() >= (index + 1);
}

float Settings::levelCompletionTime(unsigned int index) const
{
	return m_levelCompletionTimes[index];
}

void Settings::setResolution(int width, int height)
{
	m_width = width;
	m_height = height;
}

void Settings::increaseSoundVolume()
{
	m_soundVolume = std::min(100, m_soundVolume + 10);
}

void Settings::decreaseSoundVolume()
{
	m_soundVolume = std::max(0, m_soundVolume - 10);
}

void Settings::increaseMusicVolume()
{
	m_musicVolume = std::min(100, m_musicVolume + 10);
}

void Settings::decreaseMusicVolume()
{
	m_musicVolume = std::max(0, m_musicVolume - 10);
}

void Settings::setLastSelectedLevel(int lastSelectedLevel)
{
	m_lastSelectedLevel = lastSelectedLevel;
}

void Settings::markLevelAsCompleted(unsigned int index, float levelCompletionTime)
{
	if (m_levelCompletionTimes.size() >= (index + 1))
	{
		if (m_levelCompletionTimes[index] >= levelCompletionTime)
		{
			m_levelCompletionTimes[index] = levelCompletionTime;
		}
	}
	else
	{
		m_levelCompletionTimes << levelCompletionTime;
	}
}

BinaryStream &operator >>(BinaryStream &stream, Settings &settings)
{
	stream >> settings.m_width;
	stream >> settings.m_height;
	stream >> settings.m_soundVolume;
	stream >> settings.m_musicVolume;
	stream >> settings.m_lastSelectedLevel;
	stream >> settings.m_levelCompletionTimes;

	return stream;
}

BinaryStream &operator <<(BinaryStream &stream, const Settings &settings)
{
	stream << settings.m_width;
	stream << settings.m_height;
	stream << settings.m_soundVolume;
	stream << settings.m_musicVolume;
	stream << settings.m_lastSelectedLevel;
	stream << settings.m_levelCompletionTimes;

	return stream;
}
