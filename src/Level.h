#ifndef LEVEL_H
#define LEVEL_H

#include <SDL2/SDL.h>

#include <vector>

#include "ImageWrapper.h"
#include "LevelTile.h"

class Goal;
class Spawn;

class Level
{
	friend BinaryStream &operator >>(BinaryStream &stream, Level &level);

	public:
		Level(Renderer &renderer);

		SDL_Texture *tileset();

		int width() const;
		int height() const;

		template<class T>
		const T *findTile() const
		{
			for (const LevelTile &tile : tiles())
			{
				for (IDrawable *drawable : tile.objects())
				{
					T *o = dynamic_cast<T *>(drawable);

					if (o)
					{
						return o;
					}
				}
			}

			return nullptr;
		}

		std::vector<LevelTile> tiles() const;

	private:
		ImageWrapper m_tileset;

		std::vector<LevelTile> m_tiles;

		int m_width;
		int m_height;
};

#endif // LEVEL_H
