#pragma once
#include "../graphics/window.h"
#include "map.h"
#include "../graphics/graphics.h"

class Game
{
	Map*		_map;
public:
	Game();
	~Game();
	void update();
	void render(Graphics* g);
};