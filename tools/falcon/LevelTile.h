#ifndef LEVELTILE_H
#define LEVELTILE_H

#include <QDataStream>

class LevelTile
{
	friend QDataStream &operator <<(QDataStream &stream, const LevelTile &tile);

	public:
		LevelTile(int id, int x, int y);

	private:
		int m_id;
		int m_x;
		int m_y;
};

#endif // LEVELTILE_H
