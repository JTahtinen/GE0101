#include "application.h"
#include "../graphics/graphics.h"
#include "../math/vec2.h"
#include <SDL2/SDL.h>
#include "../graphics/renderer.h"
#include "../input/input.h"
#include "../util/log.h"
#include "../game/scenegraph.h"

Log gameLog;
Renderer* renderer;

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


	Renderer r(&_window, &g);
	renderer = &r;
	
	Surface* snowman = Surface::loadSurface("res/IMG_2086.JPG");
	Vec2 pos(10, 10);

	Input& in = Input::instance();

	while (running)
	{
		in.update();
		testSurface.clear();
		if (in.poll(KEY_ESCAPE))
		{
			running = false;
		}

		_game.update();
		g.drawSurfaceAbs(snowman, 0, 0, 800, 600);
		//renderer->submit(&renderable);
		renderer->flush();
		//_game.render(&g);
		_window.applySurface(&testSurface);
		_window.update();
	}

	delete snowman;
	snowman = nullptr;
}