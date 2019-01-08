#include "application.h"
#include "../graphics/graphics.h"
#include "../math/vec2.h"
#include <SDL2/SDL.h>
#include "../graphics/renderer.h"

Application::Application()
	: _window(800, 600, "GE0101")
{
}

void Application::run()
{
	bool running = true;
	Surface testSurface = _window.createDrawSurface();
	Graphics g;
	g.setTarget(&testSurface);
	SDL_Event ev;

	Surface s(12, 12);

	Renderer renderer(&_window, &g);
	
	Surface* snowman = Surface::loadSurface("res/IMG_2086.JPG");
	Vec2 pos(10, 10);
	Renderable renderable(&s, pos);

	while (running)
	{
		testSurface.clear();
		while (SDL_PollEvent(&ev))
		{
			if (ev.type == SDL_KEYDOWN)
			{
				switch (ev.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					running = false;
					break;
				case SDLK_LEFT:
					pos.x--;
					break;
				case SDLK_RIGHT:
					pos.x++;
					break;
				case SDLK_UP:
					pos.y--;
					break;
				case SDLK_DOWN:
					pos.y++;
					break;
				}
			}
		}

		_game.update();
		g.drawSurfaceAbs(snowman, 0, 0, 800, 600);
		renderer.submit(&renderable);
		renderer.flush();
		//_game.render(&g);
		_window.applySurface(&testSurface);
		_window.update();
	}

	delete snowman;
	snowman = nullptr;
}