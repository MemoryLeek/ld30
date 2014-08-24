#ifndef SETTINGS_H
#define SETTINGS_H

#include "BinaryStream.h"

class Settings
{
	friend BinaryStream &operator >>(BinaryStream &stream, Settings &settings);
	friend BinaryStream &operator <<(BinaryStream &stream, const Settings &settings);

	public:
		Settings();

		int width() const;
		int height() const;
		int soundVolume() const;
		int musicVolume() const;
		int lastSelectedLevel() const;
		int unlockedLevels() const;

		void setResolution(int width, int height);
		void setSoundVolume(int volume);
		void setMusicVolume(int volume);
		void setLastSelectedLevel(int lastSelectedLevel);
		void setUnlockedLevels(int unlockedLevels);

	private:
		int m_width;
		int m_height;
		int m_soundVolume;
		int m_musicVolume;
		int m_lastSelectedLevel;
		int m_unlockedLevels;
};

#endif // SETTINGS_H
