#ifndef LEVELTILE_H
#define LEVELTILE_H

#include <QDataStream>
#include <QList>

#include "LevelTileLayer.h"
#include "LevelTileMapObject.h"

class LevelTile
{
	friend QDataStream &operator <<(QDataStream &stream, const LevelTile &tile);

	public:
		LevelTile(int x, int y);

		void addLayer(LevelTileLayer layer);
		void setWalkable(bool walkable);
		void addMapObject(LevelTileMapObject object);

	private:
		QList<LevelTileLayer> m_layers;
		QList<LevelTileMapObject> m_objects;

		bool m_walkable;

		int m_x;
		int m_y;
};

#endif // LEVELTILE_H
