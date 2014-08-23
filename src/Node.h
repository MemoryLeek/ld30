#ifndef NODE_H
#define NODE_H

class Node
{
	public:
		Node(float x, float y, float angle, Node *parent = nullptr);

		float x() const;
		void setX(float x);
		void moveX(float x);
		float y() const;
		void setY(float y);
		void moveY(float y);
		float angle() const;
		void setAngle(float angle);

	private:
		float m_x;
		float m_y;
		float m_angle;
		Node *m_parent;
};

#endif // NODE_H
