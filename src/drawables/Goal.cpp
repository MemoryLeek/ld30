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
	SDL_Rect target = { m_x - TILE_SIZE / 2 - renderer.cameraOffsetX(), m_y - TILE_SIZE / 2 - renderer.cameraOffsetY(), TILE_SIZE, TILE_SIZE };
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawRect(renderer, &target);
}
