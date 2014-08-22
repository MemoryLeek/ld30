#include "StringEx.h"

StringToken::StringToken(const std::string &value)
{
	m_value = value;
}

StringToken::StringToken(const int value)
{
	m_value = std::to_string(value);
}

StringToken::operator std::string() const
{
	return m_value;
}
