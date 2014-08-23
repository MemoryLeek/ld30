#ifndef LEVELTILELAYER_H
#define LEVELTILELAYER_H

#include <QDataStream>

class LevelTileLayer
{
	friend QDataStream &operator <<(QDataStream &stream, const LevelTileLayer &layer);

	public:
		LevelTileLayer(int id);

		int id() const;

	private:
		int m_id;
};

#endif // LEVELTILELAYER_H
