#ifndef IMAGEWRAPPER_H
#define IMAGEWRAPPER_H

#include <SDL2/SDL_image.h>

#include "BinaryStream.h"

class Renderer;

class ImageWrapper
{
	friend BinaryStream &operator >>(BinaryStream &stream, ImageWrapper &wrapper);

	public:
		ImageWrapper();

		operator SDL_Texture *() const;

	private:
		SDL_Texture *m_texture;
};

#endif // IMAGEWRAPPER_H
