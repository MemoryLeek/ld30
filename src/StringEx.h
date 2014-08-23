#ifndef STRINGEX_H
#define STRINGEX_H

#include <list>
#include <string>
#include <sstream>
#include <algorithm>

class StringToken
{
	public:
		StringToken(const std::string &value);
		StringToken(int value);
		StringToken(float value);

		operator std::string() const;

	private:
		std::string m_value;
};

class StringEx
{
	public:
		template<class ...TArguments>
		static std::string format(const std::string &format, TArguments ...arguments)
		{
			std::string target = format;
			std::list<StringToken> strings = { arguments... };
			std::list<StringToken>::const_iterator iterator = strings.begin();

			for (int i = 1; iterator != strings.end(); iterator++, i++)
			{
				std::ostringstream stream;
				stream << "%";
				stream << i;

				const std::string &placeholder = stream.str();
				const std::string current = *iterator;

				const int position = target.find(placeholder);
				const int length = placeholder.length();

				target.replace(position, length, current);
			}

			return target;
		}
};

#endif // STRINGEX_H
