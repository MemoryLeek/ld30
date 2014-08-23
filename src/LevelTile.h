#ifndef LEVELTILE_H
#define LEVELTILE_H

#include "BinaryStream.h"

const int TILE_SIZE = 32;

class LevelTile
{
	friend BinaryStream &operator >>(BinaryStream &stream, LevelTile &tile);

	public:
		LevelTile();

		int id() const;
		int x() const;
		int y() const;

	private:
		int m_id;
		int m_x;
		int m_y;
};

#endif // LEVELTILE_H
