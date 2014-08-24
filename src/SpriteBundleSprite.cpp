#include <iostream>

#include "SpriteBundleSprite.h"
#include "Util.h"

SpriteBundleSprite::SpriteBundleSprite()
	: m_index(0)
	, m_delay(0)
	, m_loops(0)
{

}

void SpriteBundleSprite::update(const int delta)
{
	const float f = (delta / 1000.0f) * (1000.0f / m_delay);
	const float candidate = m_index + f;
	const float count = m_frames.size();

	if(candidate > count)
	{
		if(m_loops <= 0)
		{
			m_index = 0;
		}
	}
	else
	{
		m_index = candidate;
	}
}

SDL_Texture *SpriteBundleSprite::currentFrame() const
{
	return m_frames[m_index];
}

int SpriteBundleSprite::delay() const
{
	return m_delay;
}

int SpriteBundleSprite::frameCount() const
{
	return m_frames.size();
}

BinaryStream &operator >>(BinaryStream &stream, SpriteBundleSprite &sprite)
{
	stream >> sprite.m_delay;
	stream >> sprite.m_frames;
	stream >> sprite.m_loops;

	return stream;
}
