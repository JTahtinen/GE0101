#pragma once
#include "../graphics/window.h"
#include "../game/game.h"

class Application
{
	Game			_game;
	Window			_window;
public:
	Application();
	void run();
};