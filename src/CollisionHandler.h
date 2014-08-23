#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H

#include <vector>

#include <SDL2/SDL_rect.h>

class Level;
class Player;
class Renderer; // REMOVE LATER

class CollisionHandler
{
	public:
		static void resolveCollisions(std::vector<Player*> dynamicObjects, const Level *level);
		static bool isPlayerInWall(const Player &player, const Level &level);

	private:
		static bool intersects(const SDL_Rect &a, const SDL_Rect &b);
		static std::pair<int, int> overlap(const SDL_Rect &a, const SDL_Rect &b);
		static void resolveCollision(Player *dynamicObject, const SDL_Rect &staticGeometry);
};

#endif // COLLISIONHANDLER_H
