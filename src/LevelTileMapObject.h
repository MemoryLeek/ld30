#ifndef LEVELTILEMAPOBJECT_H
#define LEVELTILEMAPOBJECT_H

#include "BinaryStream.h"

class LevelTileMapObject
{
	friend BinaryStream &operator >>(BinaryStream &stream, LevelTileMapObject &object);

	public:
		enum MapObjects
		{
			Spawn,
			Goal
		};

		LevelTileMapObject();

		int id() const;

	private:
		int m_id;
};

#endif // LEVELTILEMAPOBJECT_H
