#ifndef BINARYSTREAM_H
#define BINARYSTREAM_H

#include <fstream>
#include <vector>

class Renderer;

class BinaryStream
{
	friend BinaryStream &operator >>(BinaryStream &stream, int &value);
	friend BinaryStream &operator <<(BinaryStream &stream, const int &value);
	friend BinaryStream &operator >>(BinaryStream &stream, unsigned int &value);
	friend BinaryStream &operator <<(BinaryStream &stream, const unsigned int &value);
	friend BinaryStream &operator >>(BinaryStream &stream, bool &value);
	friend BinaryStream &operator <<(BinaryStream &stream, const bool &value);
	friend BinaryStream &operator >>(BinaryStream &stream, float &value);
	friend BinaryStream &operator <<(BinaryStream &stream, const float &value);

	public:
		BinaryStream(std::fstream &subject, Renderer *renderer);

		char *read(const unsigned int length);

		Renderer *renderer() const;

	private:
		std::fstream &m_subject;

		Renderer *m_renderer;
};

template<class T>
BinaryStream &operator >>(BinaryStream &stream, std::vector<T> &vector)
{
	unsigned int size = 0;
	stream >> size;

	for(unsigned int i = 0; i < size; i++)
	{
		T t;
		stream >> t;

		vector.push_back(t);
	}

	return stream;
}

template<class T>
BinaryStream &operator <<(BinaryStream &stream, const std::vector<T> &vector)
{
	unsigned int size = vector.size();
	stream << size;

	for(const T &t : vector)
	{
		stream << t;
	}

	return stream;
}

#endif // BINARYSTREAM_H
