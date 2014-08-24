#ifndef UTIL_H
#define UTIL_H

#include <math.h>
#include <vector>

template<class T1, class T2>
std::vector<T1> &operator <<(std::vector<T1> &vector, T2 element)
{
	vector.push_back(element);

	return vector;
}

#endif // UTIL_H
