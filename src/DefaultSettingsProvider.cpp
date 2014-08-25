#include <iostream>

#include "DefaultSettingsProvider.h"

Settings DefaultSettingsProvider::load()
{
	std::cout << "DEBUG: Loading defaults" << std::endl;

	Settings settings;
	settings.setResolution(1024, 768);

	return settings;
}

void DefaultSettingsProvider::save(const Settings &)
{

}
