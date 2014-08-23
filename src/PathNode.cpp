#include <iostream>

#include <cmath>

#include "PathNode.h"

PathNode::PathNode(int tileX, int tileY, const PathNode *parent, const PathNode *target)
	: m_x(tileX)
	, m_y(tileY)
	, m_parent(parent)
	, m_heuristic(0)
{
	if(target)
	{
		m_heuristic = 10 * (std::abs(x() - target->x()) + std::abs(y() - target->y())); // Manhattan distance to target
	}
}

int PathNode::x() const
{
	return m_x;
}

int PathNode::y() const
{
	return m_y;
}

const PathNode *PathNode::parent() const
{
	return m_parent;
}

void PathNode::setParent(const PathNode *node)
{
	m_parent = node;
}

int PathNode::weight() const
{
	if(!m_parent)
	{
		return 0;
	}

	return m_parent->weight() + 10;
}

bool PathNode::operator<(const PathNode &other) const
{
	return (weight() + m_heuristic < other.weight() + other.m_heuristic);
}

bool PathNode::operator==(const PathNode &other) const
{
	return (m_x == other.m_x && m_y == other.m_y);
}

bool PathNode::operator!=(const PathNode &other) const
{
	return (m_x != other.m_x || m_y != other.m_y);
}
