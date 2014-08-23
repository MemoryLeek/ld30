#ifndef GOAL_H
#define GOAL_H

#include "IDrawable.h"

class Goal : public IDrawable
{
	public:
		Goal(int x, int y);

		void draw(double delta, Renderer &renderer) override;

	private:
		int m_x;
		int m_y;
};

#endif // GOAL_H
