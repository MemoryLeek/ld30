#ifndef PATHNODE_H
#define PATHNODE_H

class PathNode
{
	public:
		PathNode(int tileX, int tileY, const PathNode *parent, const PathNode *target);

		int x() const;
		int y() const;

		const PathNode *parent() const;
		void setParent(const PathNode *node);

		int weight() const;

		bool operator<(const PathNode &other) const;
		bool operator==(const PathNode &other) const;
		bool operator!=(const PathNode &other) const;

	private:
		int m_x;
		int m_y;
		const PathNode *m_parent;
		int m_heuristic;
};

#endif // PATHNODE_H
