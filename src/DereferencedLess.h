#ifndef DEREFERENCEDLESS_H
#define DEREFERENCEDLESS_H

#include <iostream>

template<class T>
class DereferencedLess
{
	public:
		bool operator()(const T *p1, const T *p2) const { return *p1 < *p2; }
};

#endif // DEREFERENCEDLESS_H
