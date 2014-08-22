#include <iostream>

#include "BinaryStream.h"

BinaryStream::BinaryStream(std::fstream &subject)
	: m_subject(subject)
{

}

char *BinaryStream::read(const unsigned int length)
{
	char *data = new char[length];
	m_subject.read(data, length);

	return data;
}

BinaryStream &operator >>(BinaryStream &stream, int &value)
{
	std::fstream &subject = stream.m_subject;
	subject.read((char *)&value, sizeof(int));

	return stream;
}

BinaryStream &operator <<(BinaryStream &stream, const int &value)
{
	std::fstream &subject = stream.m_subject;
	subject.write((char *)&value, sizeof(int));

	return stream;
}

BinaryStream &operator >>(BinaryStream &stream, unsigned int &value)
{
	std::fstream &subject = stream.m_subject;
	subject.read((char *)&value, sizeof(unsigned int));

	return stream;
}

BinaryStream &operator <<(BinaryStream &stream, const unsigned int &value)
{
	std::fstream &subject = stream.m_subject;
	subject.write((char *)&value, sizeof(unsigned int));

	return stream;
}

BinaryStream &operator >>(BinaryStream &stream, bool &value)
{
	std::fstream &subject = stream.m_subject;
	subject.read((char *)&value, sizeof(bool));

	return stream;
}

BinaryStream &operator <<(BinaryStream &stream, const bool &value)
{
	std::fstream &subject = stream.m_subject;
	subject.write((char *)&value, sizeof(bool));

	return stream;
}

BinaryStream &operator >>(BinaryStream &stream, float &value)
{
	std::fstream &subject = stream.m_subject;
	subject.read((char *)&value, sizeof(float));

	return stream;
}

BinaryStream &operator <<(BinaryStream &stream, const float &value)
{
	std::fstream &subject = stream.m_subject;
	subject.write((char *)&value, sizeof(float));

	return stream;
}
