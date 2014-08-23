#include <SDL2/SDL.h>

#include "Spawn.h"
#include "LevelTile.h"
#include "Renderer.h"

Spawn::Spawn(int x, int y)
	: m_x(x)
	, m_y(y)
{

}

void Spawn::draw(Renderer &renderer)
{
	SDL_Rect target = { m_x - TILE_SIZE / 2 - renderer.cameraOffsetX(), m_y - TILE_SIZE / 2 - renderer.cameraOffsetY(), TILE_SIZE, TILE_SIZE };
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawRect(renderer, &target);
}
