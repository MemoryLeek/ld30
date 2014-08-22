#include <iostream>

#include "MenuState.h"
#include "Renderer.h"

MenuState::MenuState(StateHandler &stateHandler, Renderer &renderer, SettingsHandler &settingsHandler)
	: m_stateHandler(stateHandler)
	, m_renderer(renderer)
	, m_settingsHandler(settingsHandler)
	, m_selectedIndex(0)
	, m_mouseX(0)
	, m_mouseY(0)
	, m_running(true)
	, m_itemUnderCursor(false)
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
			activate();

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

void MenuState::onMouseButtonDown(SDL_MouseButtonEvent event)
{
	switch (event.button)
	{
		case SDL_BUTTON_LEFT:
		{
			if (m_itemUnderCursor)
			{
				activate();
			}

			break;
		}
	}
}

void MenuState::onMouseButtonUp(SDL_MouseButtonEvent event)
{

}

void MenuState::onMouseMove(SDL_MouseMotionEvent event)
{
	m_itemUnderCursor = false;
	m_selectedIndex = -1;

	const std::vector<MenuItem> &availableItems = items();

	if (event.x > m_renderer.width() / 2 - 100 &&
		event.x < m_renderer.width() / 2 + 100)
	{
		const int h = availableItems.size() * 26;
		const int y = (m_renderer.height() - h) / 2;

		if (event.y > y && event.y < y + h)
		{
			m_selectedIndex = (event.y - y) / 26;
			m_itemUnderCursor = true;
		}
	}
}

void MenuState::exit()
{
	m_running = false;
}

void MenuState::cancel()
{

}

void MenuState::activate()
{
	if (m_selectedIndex >= 0)
	{
		const std::vector<MenuItem> &availableItems = items();
		const MenuItem &item = availableItems[m_selectedIndex];

		item.invoke();
	}
}
