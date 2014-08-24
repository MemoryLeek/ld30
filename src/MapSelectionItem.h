#ifndef MAPSELECTIONITEM_H
#define MAPSELECTIONITEM_H

#include <string>

#include "Level.h"

class Renderer;

class MapSelectionItem
{
	public:
		MapSelectionItem(const std::string &title, const std::string &fileName, Renderer &renderer);

		std::string title() const;

		ImageWrapper preview();

		Level &level1();
		Level &level2();

	private:
		ImageWrapper m_preview;

		Level m_level1;
		Level m_level2;

		std::string m_title;
};

#endif // MAPSELECTIONITEM_H
