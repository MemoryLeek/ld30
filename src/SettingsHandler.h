#ifndef SETTINGSHANDLER_H
#define SETTINGSHANDLER_H

#include "Settings.h"

class ISettingsProvider;

class SettingsHandler
{
	public:
		SettingsHandler(ISettingsProvider *settingsProvider);

		Settings &settings();

		void save();

	private:
		Settings m_settings;
		ISettingsProvider *m_settingsProvider;
};

#endif // SETTINGSHANDLER_H
