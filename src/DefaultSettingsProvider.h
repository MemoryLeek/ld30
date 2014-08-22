#ifndef DEFAULTSETTINGSPROVIDER_H
#define DEFAULTSETTINGSPROVIDER_H

#include "ISettingsProvider.h"

class DefaultSettingsProvider : public ISettingsProvider
{
	public:
		Settings load() override;
		void save(const Settings &settings) override;
};

#endif // DEFAULTSETTINGSPROVIDER_H
