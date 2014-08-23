#ifndef GLOBALDATASTORAGE_H
#define GLOBALDATASTORAGE_H

class GlobalDataStorage
{
	public:
		static float levelCompletionTime();
		static void setLevelCompletionTime(float time);

	private:
		static float m_levelCompletionTime;
};

#endif // GLOBALDATASTORAGE_H
