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

		bool isLevelUnlocked(unsigned int index) const;
		bool isLevelCompleted(unsigned int index) const;

		float levelCompletionTime(unsigned int index) const;

		void setResolution(int width, int height);
		void setSoundVolume(int volume);
		void setMusicVolume(int volume);
		void setLastSelectedLevel(int lastSelectedLevel);
		void markLevelAsCompleted(unsigned int index, float levelCompletionTime);

	private:
		std::vector<float> m_levelCompletionTimes;

		int m_width;
		int m_height;
		int m_soundVolume;
		int m_musicVolume;
		int m_lastSelectedLevel;
};

#endif // SETTINGS_H
