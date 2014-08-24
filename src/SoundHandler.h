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
				WorldSwitch,
				Step, // CARE! We load 10 step sounds in sequence from here to Step + 9
				Squish = Step + 10
			};
		};

		static void play(Sound::Value sound);
		static void setSoundVolume(int volume);

	private:
		static void init();

		static const int CHANNELS;
		static bool m_loaded;
		static std::map<Sound::Value, Mix_Chunk*> m_samples;
};

#endif // SOUNDHANDLER_H
