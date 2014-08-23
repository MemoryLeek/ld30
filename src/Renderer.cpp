#include <iostream>

#include "Node.h"
#include "Renderer.h"

Renderer::Renderer(SDL_Renderer *renderer)
	: m_renderer(renderer)
	, m_width(0)
	, m_height(0)
	, m_camera(nullptr)
	, m_cameraBounds({0, 0, INT32_MAX, INT32_MAX})
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
	int x = (m_camera) ? m_camera->x() - m_width / (2 * m_cameraScale) : 0;
	if(x < m_cameraBounds.x)
	{
		return m_cameraBounds.x;
	}
	if(x > m_cameraBounds.x + m_cameraBounds.w - m_width / m_cameraScale)
	{
		return m_cameraBounds.x + m_cameraBounds.w - m_width / m_cameraScale;
	}

	return x;
}

int Renderer::cameraOffsetY() const
{
	int y = (m_camera) ? m_camera->y() - m_height / (2 * m_cameraScale) : 0;
	if(y < m_cameraBounds.y)
	{
		return m_cameraBounds.x;
	}
	if(y > m_cameraBounds.y + m_cameraBounds.h - m_height / m_cameraScale)
	{
		return m_cameraBounds.y + m_cameraBounds.h - m_height / m_cameraScale;
	}
	return y;
}

void Renderer::setCamera(Node *camera, float scale)
{
	m_camera = camera;
	m_cameraScale = scale;
}

void Renderer::setCameraBounds(SDL_Rect bounds)
{
	m_cameraBounds = bounds;
}

