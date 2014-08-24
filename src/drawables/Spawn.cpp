#include <SDL2/SDL.h>

#include "Spawn.h"
#include "LevelTile.h"
#include "Renderer.h"

Spawn::Spawn(int x, int y)
	: m_x(x)
	, m_y(y)
{

}

int Spawn::x() const
{
	return m_x;
}

int Spawn::y() const
{
	return m_y;
}

void Spawn::draw(double delta, Renderer &renderer)
{

}
