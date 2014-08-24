#include "SpriteLoader.h"
#include "SpriteBundle.h"
#include "BinaryStream.h"

SpriteLoader::SpriteLoader(Renderer &renderer)
	: m_renderer(renderer)
{

}

void SpriteLoader::load(const std::string &fileName, SpriteBundle &target)
{
	std::fstream file(fileName, std::ios::in | std::ios::binary);

	if (file.is_open())
	{
		BinaryStream stream(file, &m_renderer);
		stream >> target;
	}
}
