#include "MenuState.h"
#include "Renderer.h"

MenuState::MenuState(StateHandler &stateHandler, Renderer &renderer)
	: m_stateHandler(stateHandler)
	, m_renderer(renderer)
	, m_selectedIndex(0)
	, m_running(true)
{
	m_font = TTF_OpenFont("resources/ttf/Oxygen-Regular.ttf", 20);
}

bool MenuState::update(double delta)
{
	const std::vector<MenuItem> &values = items();

	for (int i = 0; i < values.size(); i++)
	{
		const MenuItem &item = values[i];
		const std::string &text = item.text();

		SDL_Color color = { i == m_selectedIndex ? 255 : 0, 0, 0, SDL_ALPHA_OPAQUE };
		SDL_Surface *surface = TTF_RenderText_Blended(m_font, text.c_str(), color);
		SDL_Texture *texture = SDL_CreateTextureFromSurface(m_renderer, surface);
		SDL_Rect dest = { 0, 0, 0, 0 };

		SDL_QueryTexture(texture, nullptr, nullptr, &dest.w, &dest.h);

		dest.x = (m_renderer.width() - dest.w) / 2;
		dest.y = (m_renderer.height() - values.size() * dest.h) / 2 + i * dest.h;

		SDL_RenderCopy(m_renderer, texture, nullptr, &dest);
		SDL_FreeSurface(surface);
		SDL_DestroyTexture(texture);
	}

	return m_running;
}

void MenuState::onKeyDown(SDL_Keycode keyCode)
{
	const std::vector<MenuItem> &availableItems = items();

	switch (keyCode)
	{
		case SDLK_DOWN:
		{
			if (++m_selectedIndex > availableItems.size() - 1)
			{
				m_selectedIndex = 0;
			}

			break;
		}

		case SDLK_UP:
		{
			if (--m_selectedIndex < 0)
			{
				m_selectedIndex = availableItems.size() - 1;
			}

			break;
		}

		case SDLK_RETURN:
		{
			availableItems
				.at(m_selectedIndex)
				.invoke();

			break;
		}

		case SDLK_ESCAPE:
		{
			cancel();

			break;
		}
	}
}

void MenuState::onKeyUp(SDL_Keycode keyCode)
{

}

void MenuState::exit()
{
	m_running = false;
}

void MenuState::cancel()
{

}
