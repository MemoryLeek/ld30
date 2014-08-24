#ifndef GOAL_H
#define GOAL_H

#include "IDrawable.h"
#include "SpriteBundle.h"

class Goal : public IDrawable
{
	public:
		Goal(int x, int y, Renderer &renderer);

		void draw(double delta, Renderer &renderer) override;

	private:
		SpriteBundle m_bundle;

		int m_x;
		int m_y;
};

#endif // GOAL_H
