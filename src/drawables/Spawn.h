#ifndef SPAWN_H
#define SPAWN_H

#include "IDrawable.h"

class Spawn : public IDrawable
{
	public:
		Spawn(int x, int y);

		void draw(Renderer &renderer) override;

	private:
		int m_x;
		int m_y;
};

#endif // SPAWN_H
