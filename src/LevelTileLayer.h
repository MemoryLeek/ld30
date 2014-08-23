#ifndef LEVELTILELAYER_H
#define LEVELTILELAYER_H

#include "BinaryStream.h"

class LevelTileLayer
{
	friend BinaryStream &operator >>(BinaryStream &stream, LevelTileLayer &layer);

	public:
		LevelTileLayer();

		int id() const;

	private:
		int m_id;
};

#endif // LEVELTILELAYER_H
