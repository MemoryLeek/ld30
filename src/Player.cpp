#include <iostream>

#include "Player.h"
#include "Util.h"

Player::Player(float x, float y, SDL_Texture *texture)
	: Sprite(x, y, 0, texture)
{
}

void Player::draw(double delta, Renderer &renderer)
{
	const float speed = 100;
	while(!m_path.empty())
	{
		const SDL_Point &target = m_path.top();
		const SDL_Point worldTarget = {target.x * 32, target.y * 32};

		const float currentD = Util::distanceBetween(x(), y(), worldTarget.x, worldTarget.y);
//		std::cout << "Current distance to next node " << currentD << std::endl;
		if((int)y() == worldTarget.y && (int)x() == worldTarget.x)
		{
			m_path.pop();
			continue;
		}

		if((int)y() == worldTarget.y) // Walking horizontally
		{
			setY(worldTarget.y); // Align to tile
			if(x() - worldTarget.x > 0) // Move left
			{
				setX(x() - speed * delta);
			}
			else // Move right
			{
				setX(x() + speed * delta);
			}
		}
		else if((int)x() == worldTarget.x)
		{
			setX(worldTarget.x); // Align to tile
			if(y() - worldTarget.y > 0) // Move up
			{
				setY(y() - speed * delta);
			}
			else // Move down
			{
				setY(y() + speed * delta);
			}
		}

//		float newX = x();
//		if(x() - worldTarget.x > 0) // Move left
//		{
//			newX -= speed * delta;
//		}
//		else // Move right
//		{
//			newX += speed * delta;
//		}

//		float newY = y();
//		if(y() - worldTarget.y > 0) // Move left
//		{
//			newY -= speed * delta;
//		}
//		else // Move right
//		{
//			newY += speed * delta;
//		}

		const float newD = Util::distanceBetween(x(), y(), worldTarget.x, worldTarget.y);
//		std::cout << "New distance to next node " << newD << std::endl;
		if(newD > currentD)
		{
			m_path.pop();
		}
		else
		{
//			setX(newX);
//			setY(newY);
			break;
		}
	}

	Sprite::draw(delta, renderer);
}

void Player::setPath(std::stack<SDL_Point> path)
{
	m_path = path;
}
