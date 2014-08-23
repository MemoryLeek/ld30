#include "ImageWrapper.h"
#include "Renderer.h"

ImageWrapper::ImageWrapper(Renderer &renderer)
	: m_renderer(renderer)
{

}

ImageWrapper::~ImageWrapper()
{
	SDL_DestroyTexture(m_texture);
}

ImageWrapper::operator SDL_Texture *()
{
	return m_texture;
}

BinaryStream &operator >>(BinaryStream &stream, ImageWrapper &wrapper)
{
	unsigned int size = 0;

	stream >> size;

	char *data = stream.read(size);

	SDL_RWops *handle = SDL_RWFromMem(data, size);
	SDL_Surface *surface = IMG_LoadPNG_RW(handle);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(wrapper.m_renderer, surface);
	SDL_FreeSurface(surface);

	wrapper.m_texture = texture;

	return stream;
}
