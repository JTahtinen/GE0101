#pragma once
#include "../graphics/window.h"
#include "map.h"
#include "../graphics/graphics.h"
#include <vector>
#include "entity.h"

class Game
{
	Map*					_map;
	std::vector<Entity*>	_entities;
public:
	Game();
	~Game();
	void update();
	void render(Graphics* g);
	void loadResources();
};