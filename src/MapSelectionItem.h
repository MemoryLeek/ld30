#ifndef MAPSELECTIONITEM_H
#define MAPSELECTIONITEM_H

#include <string>

class MapSelectionItem
{
	public:
		MapSelectionItem(const std::string &title, const std::string &fileName);

		std::string title() const;
		std::string fileName() const;

	private:
		std::string m_title;
		std::string m_fileName;
};

#endif // MAPSELECTIONITEM_H
