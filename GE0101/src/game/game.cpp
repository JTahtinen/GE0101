#include "game.h"
#include "scenegraph.h"
#include "../input/input.h"
#include "../defs.h"
#include "../globals.h"

Game::Game(Renderer* renderer)
	: _camera(Camera(16.0f, 9.0f))
	, _renderer(renderer)
{
	ASSERT(renderer);
	_map = Map::createMap(5, 5);
	Entity* player = new Entity(Vec2(0.0f, 0.0f), &defaultSprite);
	player->addController(&_inputController);
	_entities.push_back(player);
	_entities.push_back(new Entity(Vec2(-0.5f, -0.5f), &defaultSprite));
}

Game::~Game()
{
	delete _map;
	for (auto* entity : _entities)
	{
		delete entity;
	}
}

void Game::update()
{
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

 	_camera.setPos(_entities[0]->getPos());
	_camera.update();

	_map->render(_renderer, &_camera);
	for (auto& entity : _entities)
	{
		entity->render(_renderer, &_camera);
	}
}

const Camera& Game::getCamera() const
{
	return _camera;
}