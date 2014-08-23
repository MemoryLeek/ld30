#ifndef IMAGEWRAPPER_H
#define IMAGEWRAPPER_H

#include <SDL2/SDL_image.h>

#include "BinaryStream.h"

class Renderer;

class ImageWrapper
{
	friend BinaryStream &operator >>(BinaryStream &stream, ImageWrapper &wrapper);

	public:
		ImageWrapper(Renderer &renderer);
		~ImageWrapper();

		operator SDL_Texture *();

	private:
		Renderer &m_renderer;
		SDL_Texture *m_texture;
};

#endif // IMAGEWRAPPER_H
