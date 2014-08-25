#include <iostream>

#include "MapSelectionState.h"
#include "MapSelectionToken.h"
#include "StateHandler.h"
#include "GameState.h"
#include "MainMenuState.h"
#include "SettingsHandler.h"
#include "Renderer.h"
#include "Util.h"
#include "StringEx.h"

MapSelectionState::MapSelectionState(StateHandler &stateHandler, Renderer &renderer, SettingsHandler &settingsHandler, MapSelectionToken &mapSelectionToken)
	: m_stateHandler(stateHandler)
	, m_renderer(renderer)
	, m_settingsHandler(settingsHandler)
	, m_mapSelectionToken(mapSelectionToken)
	, m_joystickReady(true)
	, m_itemUnderCursor(false)
	, m_skipped(false)
	, m_adjustSoundVolume(false)
	, m_adjustMusicVolume(false)
	, m_running(true)
{
	SDL_Surface *surface = IMG_Load("resources/gfx/menu.png");
	Settings &settings = settingsHandler.settings();

	m_selectedMap = settings.lastSelectedLevel();
	m_background = SDL_CreateTextureFromSurface(renderer, surface);
	m_mainFont = TTF_OpenFont("resources/ttf/MunroSmall.ttf", 40);
	m_subFont = TTF_OpenFont("resources/ttf/MunroSmall.ttf", 20);

	SDL_FreeSurface(surface);
}

MapSelectionState::~MapSelectionState()
{
	SDL_DestroyTexture(m_background);
}

bool MapSelectionState::update(double delta)
{
	UNUSED(delta);

	const std::vector<MapSelectionItem> &source = m_mapSelectionToken.items();
	const Settings &settings = m_settingsHandler.settings();

	SDL_RenderSetScale(m_renderer, 1, 1);
	SDL_RenderCopy(m_renderer, m_background, nullptr, nullptr);

	const unsigned int width = 3 * ITEM_WIDTH;
	const unsigned int height = (source.size() / 3) * ITEM_HEIGHT;

	for (unsigned int i = 0; i < source.size(); i += 3)
	{
		for (unsigned ii = 0; ii < 3 && ii < source.size() - i; ii++)
		{
			const int y = i / 3 * ITEM_HEIGHT - 20;
			const int x = ii * ITEM_WIDTH;
			const int ix = (m_renderer.width() - width + (ITEM_WIDTH - 256)) / 2 + x;
			const int iy = (m_renderer.height() - height + (ITEM_HEIGHT - 192)) / 2 + y;

			const bool lu = settings.isLevelUnlocked(i + ii);
			const bool lc = settings.isLevelCompleted(i + ii);

			const MapSelectionItem &map = source[i + ii];

			SDL_Rect target = { ix, iy, 256, 192 };
			SDL_RenderCopy(m_renderer, map.preview(), nullptr, &target);

			SDL_Rect lockedRect = { ix, iy, 256, 192 };
			SDL_Rect unlockedRect = { ix, iy + 61, 256, 70 };
			SDL_Rect overlayRect = lu ? unlockedRect : lockedRect;

			SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255 * 0.7);
			SDL_RenderFillRect(m_renderer, &overlayRect);

			SDL_Color textColor = { 255, 255, 255, SDL_ALPHA_OPAQUE };
			SDL_Surface *levelNameSurface = TTF_RenderText_Solid(m_mainFont, map.title().c_str(), textColor);
			SDL_Texture *levelNameTexture = SDL_CreateTextureFromSurface(m_renderer, levelNameSurface);
			SDL_Rect levelNameTarget = { 0, 0, 0, 0 };

			SDL_QueryTexture(levelNameTexture, nullptr, nullptr, &levelNameTarget.w, &levelNameTarget.h);

			levelNameTarget.x = target.x + (target.w - levelNameTarget.w) / 2;
			levelNameTarget.y = target.y + (target.h - levelNameTarget.h) / 2 - 11; /* 11 is a good number */

			SDL_RenderCopy(m_renderer, levelNameTexture, nullptr, &levelNameTarget);
			SDL_FreeSurface(levelNameSurface);
			SDL_DestroyTexture(levelNameTexture);

			// I take no responsibility for this horrible mess of code
			const std::string &subString = lu ?
				 lc ? "BEST TIME: " + StringEx::format("%1 SEC", settings.levelCompletionTime(i + ii))
					: "NOT YET COMPLETED"
					: "NOT YET UNLOCKED";

			SDL_Surface *subSurface = TTF_RenderText_Solid(m_subFont, subString.c_str(), textColor);
			SDL_Texture *subTexture = SDL_CreateTextureFromSurface(m_renderer, subSurface);
			SDL_Rect subTarget = { 0, 0, 0, 0 };

			SDL_QueryTexture(subTexture, nullptr, nullptr, &subTarget.w, &subTarget.h);

			subTarget.x = target.x + (target.w - subTarget.w) / 2;
			subTarget.y = levelNameTarget.y + levelNameTarget.h;

			SDL_RenderCopy(m_renderer, subTexture, nullptr, &subTarget);
			SDL_FreeSurface(subSurface);
			SDL_DestroyTexture(subTexture);

			if ((i + ii) == m_selectedMap)
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
	}

	SDL_Color textColor = { 255, 255, 255, SDL_ALPHA_OPAQUE };
	SDL_Rect bottomRect = { 0, 768 - 30, 1024, 30 };
	SDL_RenderFillRect(m_renderer, &bottomRect);

	const int soundVolume = settings.soundVolume();
	const int musicVolume = settings.musicVolume();

	const std::string &soundVolumeString = StringEx::format("SOUND: %1%", (soundVolume / 128.0f) * 100.0f);
	const std::string &musicVolumeString = StringEx::format("MUSIC: %1%", (musicVolume / 128.0f) * 100.0f);

	// SOUND
	SDL_Surface *soundTextSurface = TTF_RenderText_Solid(m_subFont, soundVolumeString.c_str(), textColor);
	SDL_Texture *soundTextTexture = SDL_CreateTextureFromSurface(m_renderer, soundTextSurface);
	SDL_Rect soundTextTarget = { 10, 768 - 25, 0, 0 };

	SDL_QueryTexture(soundTextTexture, nullptr, nullptr, &soundTextTarget.w, &soundTextTarget.h);
	SDL_RenderCopy(m_renderer, soundTextTexture, nullptr, &soundTextTarget);
	SDL_FreeSurface(soundTextSurface);
	SDL_DestroyTexture(soundTextTexture);

	// VOLUME
	SDL_Surface *musicTextSurface = TTF_RenderText_Solid(m_subFont, musicVolumeString.c_str(), textColor);
	SDL_Texture *musicTextTexture = SDL_CreateTextureFromSurface(m_renderer, musicTextSurface);
	SDL_Rect musicTextTarget = { 150, soundTextTarget.y, 0, 0 };

	SDL_QueryTexture(musicTextTexture, nullptr, nullptr, &musicTextTarget.w, &musicTextTarget.h);
	SDL_RenderCopy(m_renderer, musicTextTexture, nullptr, &musicTextTarget);
	SDL_FreeSurface(musicTextSurface);
	SDL_DestroyTexture(musicTextTexture);

	return m_running;
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
			if (m_itemUnderCursor)
			{
				activate();
			}

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
	m_adjustSoundVolume = event.y > (760 - 30) && event.x < 150;
	m_adjustMusicVolume = event.y > (760 - 30) && event.x > 150 && event.x < 300;
	m_itemUnderCursor = false;
	m_selectedMap = -1;

	const std::vector<MapSelectionItem> &source = m_mapSelectionToken.items();
	const Settings &settings = m_settingsHandler.settings();

	const unsigned int width = 3 * ITEM_WIDTH;
	const unsigned int height = (source.size() / 3) * ITEM_HEIGHT;

	for (unsigned int i = 0; i < source.size(); i += 3)
	{
		for (unsigned ii = 0; ii < 3 && ii < source.size() - i && settings.isLevelUnlocked(i + ii); ii++)
		{
			const int y = i / 3 * ITEM_HEIGHT;
			const int x = ii * ITEM_WIDTH;
			const int ix = (m_renderer.width() - width + (ITEM_WIDTH - 256)) / 2 + x;
			const int iy = (m_renderer.height() - height + (ITEM_HEIGHT - 192)) / 2 + y;

			if (event.x > ix && event.x < ix + ITEM_WIDTH &&
				event.y > iy && event.y < iy + 192)
			{
				m_selectedMap = (i + ii);
				m_itemUnderCursor = true;
			}
		}
	}
}

void MapSelectionState::onMouseWheel(SDL_MouseWheelEvent event)
{
	Settings &settings = m_settingsHandler.settings();

	if (m_adjustSoundVolume)
	{
		if (event.y > 0)
		{
			settings.increaseSoundVolume();
		}

		if (event.y < 0)
		{
			settings.decreaseSoundVolume();
		}
	}

	if (m_adjustMusicVolume)
	{
		if (event.y > 0)
		{
			settings.increaseMusicVolume();
		}

		if (event.y < 0)
		{
			settings.decreaseMusicVolume();
		}
	}

	const int soundVolume = settings.soundVolume();
	const int musicVolume = settings.musicVolume();

	SoundHandler::setSoundVolume(soundVolume);
	SoundHandler::setMusicVolume(musicVolume);
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

	const unsigned int unlockedLevels = m_settingsHandler
		.settings()
		.unlockedLevels();

	const unsigned int levels = source.size();
	const unsigned int max = std::min(levels - 1, unlockedLevels);

	if (!m_selectedMap--)
	{
		m_selectedMap = max;
	}
}

void MapSelectionState::right()
{
	std::vector<MapSelectionItem> &source = m_mapSelectionToken.items();

	const unsigned int unlockedLevels = m_settingsHandler
		.settings()
		.unlockedLevels();

	const unsigned int levels = source.size();
	const unsigned int max = std::min(levels - 1, unlockedLevels);

	if (m_selectedMap++ == max)
	{
		m_selectedMap = 0;
	}
}

void MapSelectionState::activate()
{
	if (!m_skipped && unsigned(-1) != m_selectedMap)
	{
		MapSelectionItem &map = m_mapSelectionToken
			.items()
			.at(m_selectedMap);

		m_mapSelectionToken
			.setMapSelection(&map);

		m_settingsHandler
			.settings()
			.setLastSelectedLevel(m_selectedMap);

		m_stateHandler
			.changeState<GameState>(true);

		m_skipped = true;
	}
}

void MapSelectionState::cancel()
{
	m_running = false;
}
