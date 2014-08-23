#include <algorithm>
#include <iostream>
#include <vector>

#include "DereferencedEqual.h"
#include "DereferencedLess.h"
#include "Level.h"
#include "Pathfinder.h"
#include "PathNode.h"

Pathfinder::Pathfinder()
{
}

std::stack<SDL_Point> Pathfinder::find(const SDL_Point &from, const SDL_Point &to) const
{
	std::stack<SDL_Point> path;

	const PathNode targetNode(to.x, to.y, nullptr, nullptr);
	PathNode *originNode = new PathNode(from.x, from.y, nullptr, &targetNode);
	if(!isWalkable(*originNode))
	{
		std::cout << "Origin node not walkable" << std::endl;
		delete originNode;
		return path;
	}

	// openList needs to be sorted by weight
	std::set<PathNode*, DereferencedLess<PathNode>> openList;
	std::vector<PathNode*> closedList;

	// Add the start node to the open list
	openList.insert(originNode);

	// Loop until we're at the target node (path found) or the open list is empty (no path to target)
	PathNode *current = *openList.begin();
	for(; current != *openList.end() && *current != targetNode; current = *openList.begin())
	{
		// Move the current node to the closed list
		openList.erase(current);
		closedList.push_back(current);

		// Ghetto LD hack for allowed directions, cba to think
		const int possibleDirecion[4][2] = {{0, -1},
											{1, 0},
											{0, 1},
											{-1, 0}};

		for(int i = 0; i < 4; i++)
		{
			PathNode node(current->x() + possibleDirecion[i][0], current->y() + possibleDirecion[i][1], current, &targetNode);

			if(node == *current)
			{
				continue;
			}

			// Skip if it isn't walkable or if it's already on the closed list
			if(!isWalkable(node) || std::find_if(closedList.begin(), closedList.end(), DereferencedEqual<PathNode>(&node)) != closedList.end())
			{
				continue;
			}

			// If it isn't on the open list it should be added there
			if(std::find_if(openList.begin(), openList.end(), DereferencedEqual<PathNode>(&node)) == openList.end())
			{
				openList.insert(new PathNode(node));
			}
			else // Already on the open list, check if this path is better
			{
				PathNode *existingNode = *std::find_if(openList.begin(), openList.end(), DereferencedEqual<PathNode>(&node));

				if(node.weight() < existingNode->weight())
				{
					// Updating parent causes the weight to change, we need to remove and add to list to sort
					openList.erase(existingNode);
					existingNode->setParent(current);
					openList.insert(existingNode);
				}
			}
		}
	}

	// If the open list still contains nodes we found our path, trace it back while converting it to pixel coords
	if(openList.size() > 0)
	{
		for(const PathNode *traceback = current; traceback != nullptr; traceback = traceback->parent())
		{
			path.push({traceback->x(), traceback->y()});
		}
	}

	// Cleanup
	for(PathNode *node : openList)
	{
		delete node;
	}

	for(PathNode *node : closedList)
	{
		delete node;
	}

	return path;
}

void Pathfinder::reload(const Level &level)
{
	m_walkables.clear();

	for(const LevelTile &tile : level.tiles())
	{
		if(tile.walkable())
		{
			m_walkables.emplace(tile.x(), tile.y());
		}
	}

	std::cout << "Pathfinder loaded " << m_walkables.size() << " walkable tiles." << std::endl;
}

bool Pathfinder::isWalkable(const PathNode &node) const
{
	const std::pair<int, int> position(node.x(), node.y());
	return m_walkables.find(position) != m_walkables.end();
}
