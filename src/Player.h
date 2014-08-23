#ifndef PLAYER_H
#define PLAYER_H

#include <stack>

#include "Sprite.h"

class Player : public Sprite
{
	public:
		Player(float x, float y, SDL_Texture *texture);

		bool isDead() const;
		void kill();
		void respawn(float x, float y);

		void draw(double delta, Renderer &renderer) override;

		void walkTowards(SDL_Point point);

	private:
		bool m_dead;
		SDL_Point m_targetPoint;
};

#endif // PLAYER_H
