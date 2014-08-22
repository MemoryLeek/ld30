#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL_render.h>

#include "Node.h"
#include "IDrawable.h"

class Renderer;

class Sprite : public Node, public IDrawable
{
	public:
		Sprite(float x, float y, float angle, SDL_Texture *texture);

		void draw(Renderer &renderer) override;

	private:
		SDL_Texture *m_texture;
		int m_width;
		int m_height;
};

#endif // SPRITE_H
