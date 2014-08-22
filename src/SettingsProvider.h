#ifndef SETTINGSPROVIDER_H
#define SETTINGSPROVIDER_H

#include <string>

#include "ISettingsProvider.h"

class SettingsProvider : public ISettingsProvider
{
	public:
		SettingsProvider(const std::string &fileName, ISettingsProvider *fallbackProvider);

		Settings load() override;
		void save(const Settings &settings) override;

	private:
		std::string m_fileName;
		ISettingsProvider *m_fallbackProvider;
};

#endif // SETTINGSPROVIDER_H
