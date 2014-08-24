#include <SDL2/SDL.h>

#include "Goal.h"
#include "LevelTile.h"
#include "Renderer.h"
#include "SpriteLoader.h"

Goal::Goal(int x, int y, Renderer &renderer)
	: m_x(x)
	, m_y(y)
{
	SpriteLoader loader(renderer);
	loader.load("resources/goal.spb", m_bundle);
}

void Goal::draw(double delta, Renderer &renderer)
{
	m_bundle.update(delta * 1000);

	int width = 0;
	int height = 0;

	SDL_Texture *texture = m_bundle.currentImage();
	SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

	SDL_Rect dest = { m_x - width / 2 - renderer.cameraOffsetX(), m_y - width / 2 - renderer.cameraOffsetY(), width, height };
	SDL_RenderCopy(renderer, texture, nullptr, &dest);
}
