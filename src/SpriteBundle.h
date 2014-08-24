#ifndef SPRITEBUNDLE_H
#define SPRITEBUNDLE_H

#include <vector>

#include "SpriteBundleSprite.h"
#include "BinaryStream.h"

class Scene;
class Renderer;

class SpriteBundle
{
	friend BinaryStream &operator >>(BinaryStream &stream, SpriteBundle &bundle);

	public:
		SpriteBundle();

		void update(const int delta);
		void setImageIndex(const int index);

		SDL_Texture *currentImage() const;

		int spriteCount() const;
		int imageIndex() const;

	protected:
		std::vector<SpriteBundleSprite> m_sprites;

	private:
		int m_index;
};

#endif // SPRITEBUNDLE_H
