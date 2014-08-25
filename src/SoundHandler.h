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

		struct Music
		{
			enum Value
			{
				Aztec,
				Tech
			};
		};

		static void play(Sound::Value sound);
		static void playMusic(Music::Value music);
		static void stopMusic();
		static void setSoundVolume(int volume);
		static void setMusicVolume(int volume);

		static void update(double delta);

	private:
		static void init();

		static const int CHANNELS;
		static bool m_loaded;
		static std::map<Sound::Value, Mix_Chunk*> m_samples;
		static std::map<Music::Value, Mix_Music*> m_tracks;
		static Music::Value m_music;

		static float m_musicPosition;
};

#endif // SOUNDHANDLER_H
