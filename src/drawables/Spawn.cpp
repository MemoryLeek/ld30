#include <SDL2/SDL.h>

#include "Spawn.h"
#include "LevelTile.h"
#include "Renderer.h"
#include "SpriteLoader.h"

Spawn::Spawn(int x, int y, Renderer &renderer)
	: m_x(x)
	, m_y(y)
{
	SpriteLoader loader(renderer);
	loader.load("resources/spawn.spb", m_bundle);
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
	m_bundle.update(delta * 1000);

	int width = 0;
	int height = 0;

	SDL_Texture *texture = m_bundle.currentImage();
	SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

	SDL_Rect dest = { m_x - width / 2 - renderer.cameraOffsetX(), m_y - width / 2 - renderer.cameraOffsetY(), width, height };
	SDL_RenderCopy(renderer, texture, nullptr, &dest);
}
