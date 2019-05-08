#include "game.h"
#include "scenegraph.h"
#include "../input/input.h"
#include "../defs.h"
#include "../globals.h"
#include "controllers/inputcontroller.h"
#include "controllers/aicontroller.h"
#include "../physics/collider.h"

float Game::frameTime = 0.0f;

Game::Game(Renderer* renderer)
	: _camera(Camera(16.0f, 9.0f))
	, _renderer(renderer)
{
	ASSERT(renderer);
	_map = Map::createMap(5, 5);
	Actor* player = new Actor(Vec2(0.0f, 0.0f), &defaultSprite, new InputController());
	addActor(player);
	_player = player;
	//addActor(new Actor(Vec2(-0.5f, -0.5f), &defaultSprite, new AIController(this)));
	addActor(new Actor(Vec2(0.5f, 0.5f), &defaultSprite));
}

Game::~Game()
{
	delete _map;
	for (auto* entity : _entities)
	{
		delete entity;
	}
}

void Game::update(float frameTime)
{
	Game::frameTime = frameTime;
	//MSG(frameTime);
	static Input& in = Input::instance();
	if (in.poll(KEY_Z, KEYSTATE_TYPED))
	{
		_camera.zoomIn();
	}
	if (in.poll(KEY_X, KEYSTATE_TYPED))
	{
		_camera.zoomOut();
	}
	_map->update(this);
	
	for (auto& entity : _entities)
	{
		entity->update(this);
	}

	Collider::instance().update();
	//_player->getPos().print();

 	_camera.setPos(_player->getPos());
	_camera.update();
	_map->render(_renderer, &_camera);
	for (auto& entity : _entities)
	{
		entity->render(_renderer, &_camera);
	}
}

void Game::addEntity(Entity* e)
{
	if (e)
	{
		_entities.push_back(e);
	}
}

void Game::addActor(Actor* e)
{
	if (e)
	{
		_actors.push_back(e);
		addEntity(e);
	}
}

const Camera& Game::getCamera() const
{
	return _camera;
}

const Actor* Game::getPlayer() const
{
	return _player;
}

const std::vector<Entity*>& Game::getEntities() const
{
	return _entities;
}
