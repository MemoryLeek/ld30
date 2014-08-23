#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL_render.h>

class Node;

class Renderer
{
	public:
		Renderer(SDL_Renderer *renderer);

		operator SDL_Renderer*() const;

		int width() const;
		int height() const;

		int cameraOffsetX() const;
		int cameraOffsetY() const;
		void setCamera(Node *camera, float scale = 1);
		void setCameraBounds(SDL_Rect bounds);

	private:
		SDL_Renderer *const m_renderer;

		int m_width;
		int m_height;
		Node *m_camera;
		SDL_Rect m_cameraBounds;
		float m_cameraScale;
};

#endif // RENDERER_H
