#include <SDL2/SDL.h>

#include "Goal.h"
#include "LevelTile.h"
#include "Renderer.h"

Goal::Goal(int x, int y)
	: m_x(x)
	, m_y(y)
{

}

int Goal::tileX() const
{
	return m_x / TILE_SIZE;
}

int Goal::tileY() const
{
	return m_y / TILE_SIZE;
}

void Goal::draw(double delta, Renderer &renderer)
{

}
