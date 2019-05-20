#pragma once
#include "../graphics/window.h"
#include "../game/game.h"
#include "../graphics/renderers/renderer.h"
#include <vector>

class Application
{
	Renderer				_renderer;
	Game*					_game;
	Window					_window;
public:
	Application();
	~Application();
	void run();
};