#include <iostream>

#include "Label.h"
#include "Renderer.h"
#include "Util.h"

namespace Ui
{
	Label::Label(int x, int y, const std::string &text, TTF_Font *font, Renderer &renderer)
		: m_x(x)
		, m_y(y)
		, m_width(0)
		, m_height(0)
		, m_font(font)
		, m_renderer(renderer)
		, m_texture(nullptr)
	{
		setText(text);
	}

	Label::~Label()
	{
		SDL_DestroyTexture(m_texture);
	}

	void Label::setText(const std::string &text)
	{
		SDL_Surface *surface = TTF_RenderText_Solid(m_font, text.c_str(), {0, 0, 0, SDL_ALPHA_OPAQUE});
		if(!surface)
		{
			std::cout << "Failed to create text surface: " << TTF_GetError() << std::endl;
			return;
		}

		// We need to destroy the old texture when updating the text
		if(m_texture)
		{
			SDL_DestroyTexture(m_texture);
		}

		m_texture = SDL_CreateTextureFromSurface(m_renderer, surface);
		if(!m_texture)
		{
			std::cout << "Failed to create text texture: " << SDL_GetError() << std::endl;
		}

		// Fetch width and height to use in draw
		SDL_QueryTexture(m_texture, nullptr, nullptr, &m_width, &m_height);

		// Text is now rendered to texture, delete the surface
		SDL_FreeSurface(surface);
	}

	void Label::draw(double delta, Renderer &renderer)
	{
		UNUSED(delta);

		if(!m_texture)
		{
			return;
		}

		const SDL_Rect dest = {m_x - renderer.cameraOffsetX(), m_y - renderer.cameraOffsetY(), m_width, m_height};
		SDL_RenderCopy(renderer, m_texture, nullptr, &dest);
	}
}
