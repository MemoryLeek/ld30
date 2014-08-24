#include <iostream>

#include "Player.h"
#include "Util.h"
#include "SpriteLoader.h"
#include "LevelTile.h"
#include "Renderer.h"

Player::Player(float x, float y, Renderer &renderer)
	: Node(x, y, 0)
	, m_dead(false)
{
	SpriteLoader loader(renderer);
	loader.load("resources/character.spb", m_bundle);
}

int Player::width() const
{
	return TILE_SIZE;
}

int Player::height() const
{
	return TILE_SIZE;
}

bool Player::isDead() const
{
	return m_dead;
}

void Player::kill()
{
	m_dead = true;
}

void Player::respawn(float x, float y)
{
	setPosition(x, y);
	m_dead = false;
}

void Player::draw(double delta, Renderer &renderer)
{
	m_bundle.update(delta * 1000);

	if(!(m_targetPoint.x == 0 && m_targetPoint.y == 0))
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

	int width = 0;
	int height = 0;

	SDL_Texture *texture = m_bundle.currentImage();
	SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

	SDL_Rect dest = { x() - width / 2 - renderer.cameraOffsetX(), y() - width / 2 - renderer.cameraOffsetY(), width, height };
	SDL_RenderCopyEx(renderer, texture, nullptr, &dest, angle(), nullptr, SDL_FLIP_NONE);
}

void Player::walkTowards(SDL_Point point)
{
	m_targetPoint = point;
}

void Player::setIsWalking(bool isWalking)
{
	m_bundle.setImageIndex(isWalking);
}
