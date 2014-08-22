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

		void setResolution(int width, int height);

	private:
		int m_width;
		int m_height;
};

#endif // SETTINGS_H
