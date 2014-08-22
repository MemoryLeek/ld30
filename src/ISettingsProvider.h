#ifndef ISETTINGSPROVIDER_H
#define ISETTINGSPROVIDER_H

#include "Settings.h"

class ISettingsProvider
{
	public:
		virtual Settings load() = 0;
		virtual void save(const Settings &settings) = 0;
};

#endif // ISETTINGSPROVIDER_H
