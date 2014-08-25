#include <iostream>

#include "LevelBundle.h"
#include "MapSelectionItem.h"

MapSelectionItem::MapSelectionItem(const std::string &title, const std::string &fileName, Renderer &renderer)
	: m_title(title)
{
	std::fstream file(fileName, std::ios::in | std::ios::binary);

	if (file.is_open())
	{
		LevelBundle bundle(m_preview, m_level1, m_level2);
		BinaryStream stream(file, &renderer);
		stream >> bundle;
	}
}

std::string MapSelectionItem::title() const
{
	return m_title;
}

ImageWrapper MapSelectionItem::preview() const
{
	return m_preview;
}

Level &MapSelectionItem::level1()
{
	return m_level1;
}

Level &MapSelectionItem::level2()
{
	return m_level2;
}
