#ifndef UTIL_H
#define UTIL_H

#include <math.h>
#include <vector>

class Util
{
	public:
		static float distanceBetween(float x1, float y1, float x2, float y2)
		{
			const float xDist = x2 - x1;
			const float yDist = y2 - y1;
			return sqrtf(xDist * xDist + yDist * yDist);
		}
};

template<class T1, class T2>
std::vector<T1> &operator <<(std::vector<T1> &vector, T2 element)
{
	vector.push_back(element);

	return vector;
}

#endif // UTIL_H
