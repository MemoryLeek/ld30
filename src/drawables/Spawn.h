#ifndef SPAWN_H
#define SPAWN_H

#include "IDrawable.h"
#include "SpriteBundle.h"

class Spawn : public IDrawable
{
	public:
		Spawn(int x, int y, Renderer &renderer);

		int x() const;
		int y() const;

		void draw(double delta, Renderer &renderer) override;

	private:
		SpriteBundle m_bundle;

		int m_x;
		int m_y;
};

#endif // SPAWN_H
