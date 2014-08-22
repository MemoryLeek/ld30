#ifndef MENUITEM_H
#define MENUITEM_H

#include <string>
#include <functional>

class MenuItem
{
	public:
		MenuItem(const std::string &text, std::function<void()> callback);

		std::string text() const;

		void invoke() const;

	private:
		std::string m_text;
		std::function<void()> m_callback;
};

#endif // MENUITEM_H
