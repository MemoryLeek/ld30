#ifndef LEVEL_H
#define LEVEL_H

#include <QImage>
#include <QList>

#include "LevelTile.h"

class Level
{
	friend QDataStream &operator <<(QDataStream &stream, const Level &level);

	public:
		Level(int width, int height, QImage tileset);

		void addTile(LevelTile tile);

	private:
		QImage m_tileset;
		QList<LevelTile> m_tiles;

		int m_width;
		int m_height;
};

#endif // LEVEL_H
