#include <iostream>

#include "SpriteBundle.h"
#include "Util.h"

SpriteBundle::SpriteBundle()
	: m_index(0)
{

}

void SpriteBundle::update(const int delta)
{
	SpriteBundleSprite &image = m_sprites[m_index];
	image.update(delta);
}

void SpriteBundle::setImageIndex(const int index)
{
	m_index = index;
}

SDL_Texture *SpriteBundle::currentImage() const
{
	const SpriteBundleSprite &image = m_sprites[m_index];

	return image.currentFrame();
}

int SpriteBundle::spriteCount() const
{
	return m_sprites.size();
}

int SpriteBundle::imageIndex() const
{
	return m_index;
}

BinaryStream &operator >>(BinaryStream &stream, SpriteBundle &bundle)
{
	stream >> bundle.m_sprites;

	return stream;
}
