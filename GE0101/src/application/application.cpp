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
	

	Renderable renderable(&s, Vec2(10, 10));

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
				}
			}
		}

		_game.update();
		renderer.submit(&renderable);
		renderer.flush();
		//_game.render(&g);
		_window.applySurface(&testSurface);
		_window.update();
	}
}