#ifndef LEVELBUNDLE_H
#define LEVELBUNDLE_H

#include "Level.h"
#include "ImageWrapper.h"
#include "BinaryStream.h"

class LevelBundle
{
	friend BinaryStream &operator >>(BinaryStream &stream, LevelBundle &bundle);

	public:
		LevelBundle(ImageWrapper &preview, Level &level1, Level &level2);

	private:
		ImageWrapper &m_preview;

		Level &m_level1;
		Level &m_level2;
};

#endif // LEVELBUNDLE_H
