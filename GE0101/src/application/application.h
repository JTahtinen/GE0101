#pragma once
#include "../graphics/window.h"
#include "../game/game.h"
#include "../graphics/renderers/renderer.h"
#include <vector>
#include "../graphics/layer.h"

class Application
{
	Layer*					_layer;
	Game*					_game;
	Window					_window;
public:
	Application();
	~Application();
	void run();
private:
	void loadGlobalData();
	void deleteGlobalData();
};