#ifndef SPRITEBUNDLESPRITE_H
#define SPRITEBUNDLESPRITE_H

#include <vector>

#include "BinaryStream.h"
#include "ImageWrapper.h"

class SpriteBundleSprite
{
	friend BinaryStream &operator >>(BinaryStream &stream, SpriteBundleSprite &sprite);

	public:
		SpriteBundleSprite();

		void update(const int delta);

		SDL_Texture *currentFrame() const;

		int delay() const;
		int frameCount() const;

	private:
		std::vector<ImageWrapper> m_frames;

		float m_index;

		int m_delay;
		int m_loops;
};

#endif // SPRITEBUNDLESPRITE_H
