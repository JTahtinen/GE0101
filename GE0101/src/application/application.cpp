#include "application.h"
#include "../graphics/graphics.h"
#include "../math/vec2.h"
#include <SDL2/SDL.h>

Application::Application()
	: _window(800, 600, "GE0101")
{
}

void Application::run()
{
	bool running = true;
	Surface testSurface = _window.createDrawSurface();
	Graphics g;
	Vec2 point(0, 0);
	g.setTarget(&testSurface);
	SDL_Event ev;
	
	int dir = 1;
	while (running)
	{
		if (point.y > 1.4f)
		{
			dir = -1;
		}
		else if (point.y < -1.4f)
		{
			dir = 1;
		}
		point.x += dir * 0.0001f;
		point.y += dir * 0.0005f;
		testSurface.clear();
		//g.drawRect(point.x, point.y, point.x + 0.2f, point.y + 0.2f, 0xff0000);
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
		_game.render(&g);
		_window.applySurface(&testSurface);
		_window.update();
	}
}