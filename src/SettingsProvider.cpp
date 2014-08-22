#include <iostream>

#include "BinaryStream.h"
#include "SettingsProvider.h"

SettingsProvider::SettingsProvider(const std::string &fileName, ISettingsProvider *fallbackProvider)
	: m_fileName(fileName)
	, m_fallbackProvider(fallbackProvider)
{

}

Settings SettingsProvider::load()
{
	std::cout << "DEBUG: Loading persisted settings" << std::endl;
	std::fstream file(m_fileName, std::ios::in | std::ios::binary);

	if(file.is_open())
	{
		Settings settings;
		BinaryStream stream(file);
		stream >> settings;

		return settings;
	}
	else
	{
		return m_fallbackProvider->load();
	}
}

void SettingsProvider::save(const Settings &settings)
{
	std::cout << "DEBUG: Persisting settings" << std::endl;
	std::fstream file(m_fileName, std::ios::out | std::ios::binary);

	BinaryStream stream(file);
	stream << settings;
}
