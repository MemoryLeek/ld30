#include <iostream>

#include "DefaultSettingsProvider.h"

Settings DefaultSettingsProvider::load()
{
	std::cout << "DEBUG: Loading defaults" << std::endl;

	Settings settings;
	settings.setResolution(800, 600);

	return settings;
}

void DefaultSettingsProvider::save(const Settings &)
{

}
