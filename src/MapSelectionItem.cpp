#include "MapSelectionItem.h"

MapSelectionItem::MapSelectionItem(const std::string &title, const std::string &fileName)
	: m_title(title)
	, m_fileName(fileName)
{

}

std::string MapSelectionItem::title() const
{
	return m_title;
}

std::string MapSelectionItem::fileName() const
{
	return m_fileName;
}
