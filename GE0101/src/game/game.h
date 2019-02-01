#pragma once
#include "../graphics/window.h"
#include "map.h"
#include <vector>
#include "entity.h"
#include "camera.h"
#include "inputcontroller.h"

class Game
{
	Map*					_map;
	std::vector<Entity*>	_entities;
	Camera					_camera;
	InputController			_inputController;
public:
	Game();
	~Game();
	void update();
	const Camera& getCamera() const;
};