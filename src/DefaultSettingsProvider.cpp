#include <iostream>

#include "DefaultSettingsProvider.h"

Settings DefaultSettingsProvider::load()
{
	std::cout << "DEBUG: Loading defaults" << std::endl;

	Settings settings;
	settings.setResolution(800, 600);
	settings.setSoundVolume(128);
	settings.setMusicVolume(128);

	return settings;
}

void DefaultSettingsProvider::save(const Settings &)
{

}
