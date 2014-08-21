#include "Node.h"
#include "Renderer.h"

Renderer::Renderer(SDL_Renderer *renderer)
	: m_renderer(renderer)
	, m_width(0)
	, m_height(0)
	, m_camera(nullptr)
{
	SDL_GetRendererOutputSize(m_renderer, &m_width, &m_height);
}

Renderer::operator SDL_Renderer*() const
{
	return m_renderer;
}

int Renderer::width() const
{
	return m_width;
}

int Renderer::height() const
{
	return m_height;
}

int Renderer::cameraOffsetX() const
{
	return (m_camera) ? m_camera->x() - m_width / 2 : 0;
}

int Renderer::cameraOffsetY() const
{
	return (m_camera) ? m_camera->y() - m_height / 2 : 0;
}

void Renderer::setCamera(Node *camera)
{
	m_camera = camera;
}

