#ifndef LEVELTILE_H
#define LEVELTILE_H

#include "BinaryStream.h"
#include "LevelTileLayer.h"

const int TILE_SIZE = 32;

class LevelTile
{
	friend BinaryStream &operator >>(BinaryStream &stream, LevelTile &tile);

	public:
		LevelTile();

		std::vector<LevelTileLayer> layers() const;

		bool walkable() const;

		int x() const;
		int y() const;

	private:
		std::vector<LevelTileLayer> m_layers;

		bool m_walkable;

		int m_x;
		int m_y;
};

#endif // LEVELTILE_H
