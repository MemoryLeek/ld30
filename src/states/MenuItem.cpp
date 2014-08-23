#include "MenuItem.h"
#include "Renderer.h"
#include "SoundHandler.h"

MenuItem::MenuItem(const std::string &text, std::function<void()> callback)
	: m_text(text)
	, m_callback(callback)
{

}

std::string MenuItem::text() const
{
	return m_text;
}

void MenuItem::invoke() const
{
	SoundHandler::play(SoundHandler::Sound::Click);
	m_callback();
}

//void MenuItem::draw(Renderer &renderer)
//{

//}
