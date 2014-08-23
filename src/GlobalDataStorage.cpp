#include "GlobalDataStorage.h"

float GlobalDataStorage::m_levelCompletionTime = 0;

float GlobalDataStorage::levelCompletionTime()
{
	return m_levelCompletionTime;
}

void GlobalDataStorage::setLevelCompletionTime(float time)
{
	m_levelCompletionTime = time;
}
