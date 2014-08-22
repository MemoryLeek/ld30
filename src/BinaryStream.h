#ifndef BINARYSTREAM_H
#define BINARYSTREAM_H

#include <fstream>

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
		BinaryStream(std::fstream &subject);

		char *read(const unsigned int length);

	private:
		std::fstream &m_subject;
};

#endif // BINARYSTREAM_H
