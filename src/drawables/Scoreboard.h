#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>

#include "IDrawable.h"

class Scoreboard : public IDrawable
{
	public:
		Scoreboard(Renderer &renderer);
		~Scoreboard();

		void setTime(float time);

		void draw(double delta, Renderer &renderer) override;

	private:
		Renderer &m_renderer;
		TTF_Font *m_font;
		SDL_Texture *m_boardTexture;
		SDL_Rect m_boardDest;

		SDL_Texture *m_timeTexture;
		SDL_Rect m_timeDest;

		float m_fadeIn;
};

#endif // SCOREBOARD_H
