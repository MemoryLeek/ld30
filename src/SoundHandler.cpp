#include <iostream>
#include <sstream>

#include <SDL2/SDL_mixer.h>

#include "SoundHandler.h"

const int SoundHandler::CHANNELS = 32;
bool SoundHandler::m_loaded = false;
std::map<SoundHandler::Sound::Value, Mix_Chunk*> SoundHandler::m_samples;

void SoundHandler::play(SoundHandler::Sound::Value sound)
{
	if(!m_loaded)
	{
		init();
	}

	// Check that the sound is loaded
	if(m_samples.find(sound) == m_samples.end())
	{
		std::cout << "Sample " << sound << " not loaded.";
		return;
	}

	// Find a free channel
	for(int i = 0; i < CHANNELS; i++)
	{
		if(!Mix_Playing(i))
		{
			// Play sample
			Mix_PlayChannel(i, m_samples[sound], 0);
			break;
		}
	}
}

void SoundHandler::init()
{
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0)
	{
		std::cout << "Failed to open audio device: " << Mix_GetError() << std::endl;
	}
	else
	{
		Mix_AllocateChannels(CHANNELS);

		m_samples.emplace(Sound::Click, Mix_LoadWAV("resources/sfx/click.wav"));
		m_samples.emplace(Sound::WorldSwitch, Mix_LoadWAV("resources/sfx/switch.wav"));
		for(int i = 0; i < 10; i++)
		{
			std::ostringstream path;
			path << "resources/sfx/step" << i << ".wav";
			m_samples.emplace((Sound::Value)(Sound::Step + i), Mix_LoadWAV(path.str().c_str()));
		}
		m_samples.emplace(Sound::Squish, Mix_LoadWAV("resources/sfx/squish.wav"));
	}

	m_loaded = true;
}
