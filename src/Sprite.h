#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL_render.h>

#include "Node.h"

class Sprite : public Node
{
	public:
		Sprite(float x, float y, float angle, SDL_Texture *texture);

		void draw(SDL_Renderer *renderer);

	private:
		SDL_Texture *m_texture;
		int m_width;
		int m_height;
};

#endif // SPRITE_H
