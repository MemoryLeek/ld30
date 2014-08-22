#include <fstream>

#include "SettingsHandler.h"
#include "Settings.h"
#include "SettingsProvider.h"

SettingsHandler::SettingsHandler(ISettingsProvider *settingsProvider)
	: m_settingsProvider(settingsProvider)
{
	m_settings = settingsProvider->load();
}

Settings &SettingsHandler::settings()
{
	return m_settings;
}

void SettingsHandler::save()
{
	m_settingsProvider->save(m_settings);
}
