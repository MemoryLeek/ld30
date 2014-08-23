#include <SDL2/SDL.h>

#include "Goal.h"
#include "LevelTile.h"
#include "Renderer.h"

Goal::Goal(int x, int y)
	: m_x(x)
	, m_y(y)
{

}

void Goal::draw(Renderer &renderer)
{
	SDL_Rect target = { m_x - TILE_SIZE / 2 - renderer.cameraOffsetX(), m_y - TILE_SIZE / 2 - renderer.cameraOffsetY(), TILE_SIZE, TILE_SIZE };
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawRect(renderer, &target);
}
