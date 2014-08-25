#include <iomanip>
#include <sstream>
#include <iostream>

#include <SDL2/SDL_image.h>

#include "Renderer.h"
#include "Scoreboard.h"

Scoreboard::Scoreboard(Renderer &renderer)
	: m_renderer(renderer)
{
	m_font = TTF_OpenFont("resources/ttf/MunroSmall.ttf", 72);

	SDL_Surface *image = IMG_Load("resources/gfx/scoreboard.png");
	m_boardTexture = SDL_CreateTextureFromSurface(renderer, image);
	SDL_FreeSurface(image);

	SDL_QueryTexture(m_boardTexture, nullptr, nullptr, &m_boardDest.w, &m_boardDest.h);
	m_boardDest.w *= 4;
	m_boardDest.h *= 4;
	m_boardDest.x = renderer.width() / 2 - m_boardDest.w / 2;
	m_boardDest.y = renderer.height() / 2 - m_boardDest.h / 2;
}

Scoreboard::~Scoreboard()
{
	TTF_CloseFont(m_font);
	SDL_DestroyTexture(m_boardTexture);
	SDL_DestroyTexture(m_timeTexture);
}

void Scoreboard::setTime(float time)
{
	std::ostringstream timeString;
	timeString << std::setprecision(1) << std::fixed << time;

	SDL_Color black = {0, 0, 0, SDL_ALPHA_OPAQUE};
	SDL_Surface *surface = TTF_RenderText_Solid(m_font, timeString.str().c_str(), black);
	m_timeTexture = SDL_CreateTextureFromSurface(m_renderer, surface);
	SDL_FreeSurface(surface);

	SDL_QueryTexture(m_timeTexture, nullptr, nullptr, &m_timeDest.w, &m_timeDest.h);
	m_timeDest.x = m_renderer.width() / 2 - m_timeDest.w / 2;
	m_timeDest.y = m_renderer.height() / 2 - m_timeDest.h / 2 - 4;

	m_fadeIn = 0;
}

void Scoreboard::draw(double delta, Renderer &renderer)
{
	const int alpha = (m_fadeIn * 960 < 240) ? m_fadeIn * 960 : 240;
	SDL_SetTextureAlphaMod(m_boardTexture, alpha);
	SDL_SetTextureAlphaMod(m_timeTexture, alpha);

	SDL_RenderCopy(renderer, m_boardTexture, nullptr, &m_boardDest);
	SDL_RenderCopy(renderer, m_timeTexture, nullptr, &m_timeDest);

	m_fadeIn += delta;
}
