#include <iomanip>

#include "StringEx.h"

StringToken::StringToken(const std::string &value)
{
	m_value = value;
}

StringToken::StringToken(int value)
{
	m_value = std::to_string(value);
}

StringToken::StringToken(float value)
{
	std::ostringstream out;
	out << std::setprecision(3) << value;

	m_value = out.str();
}


StringToken::operator std::string() const
{
	return m_value;
}
