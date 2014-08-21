#include <cassert>

#include "Window.h"

Window::Window(int width, int height, const std::string &title)
	: m_window(nullptr)
	, m_renderer(nullptr)
	, m_isOpen(true)
{
	m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);
	assert(m_window);
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	assert(m_renderer);
}

Window::~Window()
{
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
}

bool Window::isOpen() const
{
	return m_isOpen;
}

void Window::close()
{
	m_isOpen = false;
}

void Window::clear()
{
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(m_renderer);
}

void Window::flip()
{
	SDL_RenderPresent(m_renderer);
}

SDL_Renderer *Window::renderer() const
{
	return m_renderer;
}
