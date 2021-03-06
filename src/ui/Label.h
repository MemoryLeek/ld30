#ifndef UI_LABEL_H
#define UI_LABEL_H

#include <string>

#include <SDL2/SDL_ttf.h>

#include "IDrawable.h"

namespace Ui
{
	class Label : public IDrawable
	{
		public:
			Label(int x, int y, const std::string &text, TTF_Font *font, Renderer &renderer);
			~Label();

			void setText(const std::string &text);

			void draw(double delta, Renderer &renderer) override;

		private:
			int m_x;
			int m_y;
			int m_width;
			int m_height;
			TTF_Font *const m_font;
			Renderer &m_renderer;
			SDL_Texture *m_texture;
	};
}

#endif // UI_LABEL_H
