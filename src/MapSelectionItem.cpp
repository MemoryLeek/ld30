#include "MapSelectionItem.h"

MapSelectionItem::MapSelectionItem(const std::string &title, const std::string &fileName1, const std::string &fileName2)
	: m_title(title)
	, m_fileName1(fileName1)
	, m_fileName2(fileName2)
{

}

std::string MapSelectionItem::title() const
{
	return m_title;
}

std::string MapSelectionItem::fileName1() const
{
	return m_fileName1;
}

std::string MapSelectionItem::fileName2() const
{
	return m_fileName2;
}
