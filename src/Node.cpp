#include "Node.h"

Node::Node(float x, float y, float angle)
	: m_x(x)
	, m_y(y)
	, m_angle(angle)
{
}

float Node::x() const
{
	return m_x;
}

float Node::y() const
{
	return m_y;
}

float Node::angle() const
{
	return m_angle;
}
