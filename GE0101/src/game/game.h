#pragma once
#include "../graphics/window.h"
#include "map.h"
#include <vector>
#include "entity.h"
#include "actor.h"
#include "camera.h"
#include "../graphics/renderers/renderer2d.h"

class Game
{
	Map*					_map;
	std::vector<Entity*>	_entities;
	std::vector<Actor*>		_actors;
	Actor*					_player;
	Camera					_camera;
	Renderer2D*				_renderer;
public:
	static float frameTime;
public:
	Game(Renderer2D* renderer);
	~Game();
	void update(float frameTime);
	void addEntity(Entity* e);
	void addActor(Actor* e);
	const Camera& getCamera() const;
	const Actor* getPlayer() const;
	const std::vector<Entity*>& getEntities() const;
};