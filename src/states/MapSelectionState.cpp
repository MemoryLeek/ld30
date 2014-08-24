#include <iostream>

#include "MapSelectionState.h"
#include "MapSelectionToken.h"
#include "StateHandler.h"
#include "GameState.h"
#include "MainMenuState.h"
#include "Renderer.h"
#include "Util.h"

MapSelectionState::MapSelectionState(StateHandler &stateHandler, Renderer &renderer, SettingsHandler &settingsHandler, MapSelectionToken &mapSelectionToken)
	: m_stateHandler(stateHandler)
	, m_renderer(renderer)
	, m_mapSelectionToken(mapSelectionToken)
	, m_selectedMap(0)
	, m_joystickReady(true)
{
	UNUSED(settingsHandler);

	SDL_Surface *surface = IMG_Load("resources/menu.png");

	m_background = SDL_CreateTextureFromSurface(renderer, surface);
	m_font = TTF_OpenFont("resources/ttf/MunroSmall.ttf", 40);

	SDL_FreeSurface(surface);
}

MapSelectionState::~MapSelectionState()
{
	SDL_DestroyTexture(m_background);
}

bool MapSelectionState::update(double delta)
{
	UNUSED(delta);

	std::vector<MapSelectionItem> &source = m_mapSelectionToken.items();

	SDL_RenderSetScale(m_renderer, 1, 1);
	SDL_RenderCopy(m_renderer, m_background, nullptr, nullptr);

	const int w = 300;
	const int width = source.size() * w;

	for (unsigned int i = 0; i < source.size(); i++)
	{
		const int x = i * w;
		const int ix = (m_renderer.width() - width + (w - 256)) / 2 + x;
		const int iy = (m_renderer.height() - 192) / 2;

		MapSelectionItem &map = source[i];

		SDL_Rect target = { ix, iy, 256, 192 };
		SDL_RenderCopy(m_renderer, map.preview(), nullptr, &target);

		SDL_Color color = { 255, 255, 255, SDL_ALPHA_OPAQUE };
		SDL_Surface *surface = TTF_RenderText_Solid(m_font, map.title().c_str(), color);
		SDL_Texture *texture = SDL_CreateTextureFromSurface(m_renderer, surface);
		SDL_Rect dest = { 0, 0, 0, 0 };

		SDL_QueryTexture(texture, nullptr, nullptr, &dest.w, &dest.h);

		dest.x = target.x + (target.w - dest.w) / 2;
		dest.y = target.y + (target.h - dest.h) / 2;

		SDL_RenderCopy(m_renderer, texture, nullptr, &dest);
		SDL_FreeSurface(surface);
		SDL_DestroyTexture(texture);

		if (i == m_selectedMap)
		{
			SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);
			SDL_RenderDrawRect(m_renderer, &target);

			target.x -= 1;
			target.y -= 1;
			target.w += 2;
			target.h += 2;

			SDL_RenderDrawRect(m_renderer, &target);
		}
	}

	return true;
}

void MapSelectionState::onKeyDown(SDL_Keycode keyCode)
{
	switch (keyCode)
	{
		case SDLK_LEFT: left(); break;
		case SDLK_RIGHT: right(); break;
		case SDLK_RETURN: activate(); break;
		case SDLK_ESCAPE: cancel(); break;
	}
}

void MapSelectionState::onKeyUp(SDL_Keycode keyCode)
{
	UNUSED(keyCode);
}

void MapSelectionState::onMouseButtonDown(SDL_MouseButtonEvent event)
{
	switch (event.button)
	{
		case SDL_BUTTON_LEFT:
		{
			activate();

			break;
		}
	}
}

void MapSelectionState::onMouseButtonUp(SDL_MouseButtonEvent event)
{
	UNUSED(event);
}

void MapSelectionState::onMouseMove(SDL_MouseMotionEvent event)
{
	m_selectedMap = -1;

	std::vector<MapSelectionItem> &source = m_mapSelectionToken.items();

	const int w = 300;
	const int width = source.size() * w;

	for (unsigned int i = 0; i < source.size(); i++)
	{
		const int x = i * w;
		const int ix = (m_renderer.width() - width + (w - 256)) / 2 + x;
		const int iy = (m_renderer.height() - 192) / 2;

		if (event.x > ix && event.x < ix + w &&
			event.y > iy && event.y < iy + 192)
		{
			m_selectedMap = i;
		}
	}
}

void MapSelectionState::onControllerButtonDown(SDL_ControllerButtonEvent event)
{
	switch (event.button)
	{
		case Accept: activate(); break;
		case Reject: cancel(); break;
	}
}

void MapSelectionState::onControllerButtonUp(SDL_ControllerButtonEvent event)
{
	UNUSED(event);
}

void MapSelectionState::onControllerAxisMotion(SDL_ControllerAxisEvent event)
{
	event.value = (abs(event.value) > 6000) ? event.value : 0;

	if (event.axis == Horizontal)
	{
		if (event.value != 0)
		{
			if (m_joystickReady)
			{
				m_joystickReady = false;

				if (event.value < 0)
				{
					left();
				}
				else
				{
					right();
				}
			}
		}
		else
		{
			m_joystickReady = true;
		}
	}
}

void MapSelectionState::left()
{
	std::vector<MapSelectionItem> &source = m_mapSelectionToken.items();

	if (!m_selectedMap--)
	{
		m_selectedMap = source.size() - 1;
	}
}

void MapSelectionState::right()
{
	std::vector<MapSelectionItem> &source = m_mapSelectionToken.items();

	if (m_selectedMap++ == source.size() - 1)
	{
		m_selectedMap = 0;
	}
}

void MapSelectionState::activate()
{
	if (unsigned(-1) != m_selectedMap)
	{
		MapSelectionItem &map = m_mapSelectionToken
			.items()
			.at(m_selectedMap);

		m_mapSelectionToken.setMapSelection(&map);
		m_stateHandler.changeState<GameState>(true);
	}
}

void MapSelectionState::cancel()
{
	m_stateHandler.changeState<MainMenuState>(false);
}
