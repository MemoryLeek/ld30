#include <iostream>

#include "Player.h"
#include "Util.h"

Player::Player(float x, float y, SDL_Texture *texture)
	: Sprite(x, y, 0, texture)
{
}

void Player::draw(double delta, Renderer &renderer)
{
	const float dist = Util::distanceBetween(x(), y(), m_targetPoint.x, m_targetPoint.y);
	if(dist > 16 && !(m_targetPoint.x == 0 && m_targetPoint.y == 0))
	{
		float angle = atanf((y() - m_targetPoint.y) / (x() - m_targetPoint.x)) * 180 / M_PI;
		if(x() - m_targetPoint.x > 0)
		{
			angle -= 180;
		}
		setAngle(angle);

		const float moveDistance = delta * 150;
		const float xMovement = cosf(angle * M_PI / 180) * moveDistance;
		const float yMovement = sinf(angle * M_PI / 180) * moveDistance;
		setX(x() + xMovement);
		setY(y() + yMovement);
	}

	Sprite::draw(delta, renderer);
}

void Player::walkTowards(SDL_Point point)
{
	m_targetPoint = point;
}
