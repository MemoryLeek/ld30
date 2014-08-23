#ifndef GLOBAL_H
#define GLOBAL_H

template<class T1, class T2>
std::vector<T1> &operator <<(std::vector<T1> &vector, T2 element)
{
	vector.push_back(element);

	return vector;
}

#endif // GLOBAL_H
