#ifndef PLAYER_H
#define PLAYER_H

#include <stack>

#include "Sprite.h"
#include "SpriteBundle.h"

class Player : public Node, public IDrawable
{
	public:
		Player(float x, float y, Renderer &renderer);

		int width() const;
		int height() const;

		bool isDead() const;
		void kill();
		void respawn(float x, float y);

		void draw(double delta, Renderer &renderer) override;

		void walkTowards(SDL_Point point);
		void setIsWalking(bool isWalking);

	private:
		bool m_dead;

		SpriteBundle m_bundle;
		SDL_Point m_targetPoint;
};

#endif // PLAYER_H
