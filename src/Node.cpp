#include <math.h>

#include "Node.h"

Node::Node(float x, float y, float angle, Node *parent)
	: m_x(x)
	, m_y(y)
	, m_angle(angle)
	, m_parent(parent)
{
}

float Node::x() const
{
	if(!m_parent)
	{
		return m_x;
	}

	const float hypotenuse = sqrtf(powf(m_x, 2) + powf(m_y, 2));

	// Take the base alpha and add rotation of parent node (in radians)
	const float angle = atanf(m_y / m_x) + m_parent->angle() * M_PI / 180;

	// Calculate new "real" x (adjacent)
	return m_parent->x() + cos(angle) * hypotenuse;
}

void Node::setX(float x)
{
	m_x = x;
}

void Node::moveX(float x)
{
	m_x += x;
}

float Node::y() const
{
	if(!m_parent)
	{
		return m_y;
	}

	const float hypotenuse = sqrtf(powf(m_x, 2) + powf(m_y, 2));

	// Take the base alpha and add rotation of parent node (in radians)
	const float angle = atanf(m_y / m_x) + m_parent->angle() * M_PI / 180;

	// Calculate new "real" y (opposite)
	return m_parent->y() + sin(angle) * hypotenuse;
}

void Node::setY(float y)
{
	m_y = y;
}

void Node::moveY(float y)
{
	m_y += y;
}

void Node::setPosition(float x, float y)
{
	m_x = x;
	m_y = y;
}

float Node::angle() const
{
	return m_angle;
}

void Node::setAngle(float angle)
{
	m_angle = angle;
}
