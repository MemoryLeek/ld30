#ifndef LEVELTILEMAPOBJECT_H
#define LEVELTILEMAPOBJECT_H

#include <QDataStream>

class LevelTileMapObject
{
	friend QDataStream &operator <<(QDataStream &stream, const LevelTileMapObject &object);

	public:
		LevelTileMapObject(int id);

	private:
		int m_id;
};

#endif // LEVELTILEMAPOBJECT_H
