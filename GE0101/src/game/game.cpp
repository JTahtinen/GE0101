#include "game.h"
#include "scenegraph.h"
#include "../input/input.h"
#include "../defs.h"
Game::Game()
	: _camera({ Vec2(0, 0), 16.0f / 9.0f })
{
	_map = new Map(10, 10);
	Entity* player = new Entity(Vec2(10, 10));
	player->addController(&_inputController);
	_entities.push_back(player);
	_entities.push_back(new Entity(Vec2(20, 20)));
}

Game::~Game()
{
}

void Game::update()
{
	static Input& in = Input::instance();
	if (in.poll(KEY_Z, KEYSTATE_TYPED))
	{
		++_camera.zoom;
		MSG(_camera.zoom);
	}
	if (in.poll(KEY_X, KEYSTATE_TYPED))
	{
		--_camera.zoom;
		MSG(_camera.zoom);
	}
	_map->update(this);
	for (auto& entity : _entities)
	{
		entity->update(this);
	}
	_camera.pos = _entities[0]->getPos();
}

const Camera& Game::getCamera() const
{
	return _camera;
}