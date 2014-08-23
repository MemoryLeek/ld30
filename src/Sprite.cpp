#include "Renderer.h"
#include "Sprite.h"

Sprite::Sprite(float x, float y, float angle, SDL_Texture *texture)
	: Node(x, y, angle)
	, m_texture(texture)
{
	SDL_QueryTexture(texture, nullptr, nullptr, &m_width, &m_height);
}

int Sprite::width() const
{
	return m_width;
}

int Sprite::height() const
{
	return m_height;
}

void Sprite::draw(double delta, Renderer &renderer)
{
	// x/y represents center of sprite
	const SDL_Rect dest = {(int)x() - m_width / 2 - renderer.cameraOffsetX(),
						   (int)y() - m_height / 2 - renderer.cameraOffsetY(),
						   m_width,
						   m_height};
	SDL_RenderCopyEx(renderer, m_texture, nullptr, &dest, angle(), nullptr, SDL_FLIP_NONE);
}
