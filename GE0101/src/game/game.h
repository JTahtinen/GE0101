#pragma once
#include "../graphics/window.h"
#include "map.h"
#include <vector>
#include "entity.h"
#include "actor.h"
#include "camera.h"
#include "inputcontroller.h"

class Game
{
	Map*					_map;
	std::vector<Entity*>	_entities;
	std::vector<Actor*>		_actors;
	Camera					_camera;
	InputController			_inputController;
	Renderer*				_renderer;
public:
	Game(Renderer* renderer);
	~Game();
	void update();
	void addEntity(Entity* e);
	void addActor(Actor* e);
	const Camera& getCamera() const;
	const std::vector<Entity*>& getEntities() const;
};