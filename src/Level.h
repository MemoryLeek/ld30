#ifndef LEVEL_H
#define LEVEL_H

#include <SDL2/SDL.h>

#include <vector>

#include "ImageWrapper.h"
#include "LevelTile.h"

class Level
{
	friend BinaryStream &operator >>(BinaryStream &stream, Level &level);

	public:
		Level(Renderer &renderer);

		SDL_Texture *tileset();

		int width() const;
		int height() const;

		std::vector<LevelTile> tiles() const;

	private:
		ImageWrapper m_tileset;

		std::vector<LevelTile> m_tiles;

		int m_width;
		int m_height;
};

#endif // LEVEL_H
