#ifndef SPRITELOADER_H
#define SPRITELOADER_H

#include <string>

class SpriteBundle;
class Renderer;

class SpriteLoader
{
	public:
		SpriteLoader(Renderer &renderer);

		void load(const std::string &fileName, SpriteBundle &target);

	private:
		Renderer &m_renderer;
};

#endif // SPRITELOADER_H
