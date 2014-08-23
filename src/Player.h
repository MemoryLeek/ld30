#ifndef PLAYER_H
#define PLAYER_H

#include <stack>

#include "Sprite.h"

class Player : public Sprite
{
	public:
		Player(float x, float y, SDL_Texture *texture);

		void draw(double delta, Renderer &renderer) override;

		void setPath(std::stack<SDL_Point> path);

	private:
		std::stack<SDL_Point> m_path;
};

#endif // PLAYER_H
