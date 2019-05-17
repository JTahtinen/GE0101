#pragma once
#include "../graphics/window.h"
#include "../game/game.h"
#include "../graphics/renderers/renderer2D.h"
#include "../graphics/renderers/quadrenderer.h"
#include <vector>

class Application
{
	std::vector<Renderer*>	_renderers;
	Renderer2D*				_renderer2D;
	QuadRenderer*			_quadRenderer;
	Game*					_game;
	Window					_window;
public:
	Application();
	~Application();
	void run();
};