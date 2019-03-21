#pragma once
#include "../graphics/window.h"
#include "../game/game.h"
#include "../graphics/renderers/renderer.h"

class Application
{
	Renderer*		_renderer;
	Game*			_game;
	Window			_window;
public:
	Application();
	~Application();
	void run();
};