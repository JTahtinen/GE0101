#include "game.h"
#include "scenegraph.h"

Game::Game()
{
	loadResources();
	_map = new Map(10, 10);
	const Surface* s = SceneGraph::instance().getSurface(0);
	_entities.push_back(new Entity(Vec2(10, 10), s));
}

Game::~Game()
{
}

void Game::update()
{
	_map->update(this);
	for (auto& entity : _entities)
	{
		entity->update(this);
	}
}

void Game::render(Graphics* g)
{
	_map->render(g);
}

void Game::loadResources()
{
	Surface* s = new Surface(12, 12);
	SceneGraph& scene = SceneGraph::instance();
	scene.pushSurface(s);
}