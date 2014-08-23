#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <set>
#include <stack>

#include <SDL2/SDL_rect.h>

class Level;
class PathNode;

class Pathfinder
{
	public:
		Pathfinder();

		std::stack<SDL_Point> find(const SDL_Point &from, const SDL_Point &to) const;

		void reload(const Level &level);

	private:
		bool isWalkable(const PathNode &node) const;

		std::set<std::pair<int, int>> m_walkables;
};

#endif // PATHFINDER_H
