#ifndef IDRAWABLE_H
#define IDRAWABLE_H

class Renderer;

class IDrawable
{
	public:
		virtual void draw(double delta, Renderer &renderer) = 0;
};

#endif // IDRAWABLE_H
