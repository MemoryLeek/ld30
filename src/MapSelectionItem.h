#ifndef MAPSELECTIONITEM_H
#define MAPSELECTIONITEM_H

#include <string>

class MapSelectionItem
{
	public:
		MapSelectionItem(const std::string &title, const std::string &fileName1, const std::string &fileName2);

		std::string title() const;
		std::string fileName1() const;
		std::string fileName2() const;

	private:
		std::string m_title;
		std::string m_fileName1;
		std::string m_fileName2;
};

#endif // MAPSELECTIONITEM_H
