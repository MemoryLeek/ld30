#ifndef PLAYER_H
#define PLAYER_H

#include <stack>

#include "Sprite.h"

class Player : public Sprite
{
	public:
		Player(float x, float y, SDL_Texture *texture);

		void draw(double delta, Renderer &renderer) override;

		void walkTowards(SDL_Point point);

	private:
		SDL_Point m_targetPoint;
};

#endif // PLAYER_H
