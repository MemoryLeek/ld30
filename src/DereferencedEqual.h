#ifndef DEREFERENCEDEQUAL_H
#define DEREFERENCEDEQUAL_H

template<class T>
class DereferencedEqual
{
	public:
		DereferencedEqual(const T *p1) : m_p1(p1) {}
		bool operator()(const T *p2) const { return *m_p1 == *p2; }

	private:
		const T *m_p1;
};

#endif // DEREFERENCEDEQUAL_H
