#ifndef NODE_H
#define NODE_H

class Node
{
	public:
		Node(float x, float y, float angle);

		float x() const;
		float y() const;
		float angle() const;

	private:
		float m_x;
		float m_y;
		float m_angle;
};

#endif // NODE_H
