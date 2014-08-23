#ifndef SOUNDHANDLER_H
#define SOUNDHANDLER_H

#include <map>

#include <SDL2/SDL_mixer.h>

class SoundHandler
{
	public:
		struct Sound
		{
			enum Value
			{
				Click,
				WorldSwitch
			};
		};

		static void play(Sound::Value sound);

	private:
		static void init();

		static const int CHANNELS;
		static bool m_loaded;
		static std::map<Sound::Value, Mix_Chunk*> m_samples;
};

#endif // SOUNDHANDLER_H
