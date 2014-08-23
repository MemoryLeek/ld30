#include <iostream>

#include "Renderer.h" // REMOVE LATER
#include <SDL2/SDL_render.h>

#include "CollisionHandler.h"
#include "Player.h"
#include "Level.h"

void CollisionHandler::resolveCollisions(std::vector<Player*> dynamicObjects, const Level *level)
{
	for(Player *dynamicObject : dynamicObjects)
	{
		const SDL_Rect dObjGeom = {dynamicObject->x(), dynamicObject->y(), dynamicObject->width(), dynamicObject->height()};
		for(const LevelTile &staticObject : level->tiles())
		{
			if(!staticObject.walkable())
			{
				const SDL_Rect sObjGeom = {staticObject.x() * 32, staticObject.y() * 32, 32, 32};
				if(intersects(dObjGeom, sObjGeom))
				{
					resolveCollision(dynamicObject, sObjGeom);
				}
			}
		}
	}
}

bool CollisionHandler::isPlayerInWall(const Player &player, const Level &level)
{
	const SDL_Rect dObjGeom = {player.x(), player.y(), player.width() - 4, player.height() - 4};
	for(const LevelTile &staticObject : level.tiles())
	{
		if(!staticObject.walkable())
		{
			const SDL_Rect sObjGeom = {staticObject.x() * 32, staticObject.y() * 32, 32, 32};
			if(intersects(dObjGeom, sObjGeom))
			{
				return true;
			}
		}
	}

	return false;
}

bool CollisionHandler::intersects(const SDL_Rect &a, const SDL_Rect &b)
{
	if(fabs(a.x - b.x) > a.w / 2 + b.w / 2 || fabs(a.y - b.y) > a.h / 2 + b.h / 2)
	{
		return false;
	}

	return true;
}

std::pair<int, int> CollisionHandler::overlap(const SDL_Rect &a, const SDL_Rect &b)
{
	int x = (a.x > b.x) ? -(b.x + b.w - a.x) : a.x + a.w - b.x;
	int y = (a.y > b.y) ? -(b.y + b.h - a.y) : a.y + a.h - b.y;
	return std::make_pair(x, y);
}

void CollisionHandler::resolveCollision(Player *dynamicObject, const SDL_Rect &staticGeometry)
{
	std::pair<int, int> objectOverlap = overlap({dynamicObject->x(), dynamicObject->y(), dynamicObject->width(), dynamicObject->height()}, staticGeometry);
	if(abs(objectOverlap.first) ==  abs(objectOverlap.second))
	{
		return;
	}

	if(abs(objectOverlap.first) <= abs(objectOverlap.second))
	{
		dynamicObject->moveX(-objectOverlap.first);
	}
	if(abs(objectOverlap.second) <= abs(objectOverlap.first))
	{
		dynamicObject->moveY(-objectOverlap.second);
	}
}
