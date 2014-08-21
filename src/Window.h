#ifndef WINDOW_H
#define WINDOW_H

#include <string>

#include <SDL2/SDL_render.h>

class Window
{
	public:
		Window(int width, int height, const std::string &title);
		~Window();

		bool isOpen() const;
		void close();

		void clear();
		void flip();

	private:
		SDL_Window *m_window;
		SDL_Renderer *m_renderer;

		bool m_isOpen;
};

#endif // WINDOW_H
