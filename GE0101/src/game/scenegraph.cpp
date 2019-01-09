#include "scenegraph.h"
#include "../globals.h"

SceneGraph::SceneGraph()
{
	_entities.reserve(100);
	_surfaces.reserve(100);
}

SceneGraph::~SceneGraph()
{
	for (auto* entity : _entities)
	{
		delete entity;
	}

	for (auto* surface : _surfaces)
	{
		delete surface;
	}
}

void SceneGraph::pushEntity(const Entity* entity)
{
	if (!entity)
	{
		gameLog.warning("Could not add null entity to scenegraph!");
	}
	_entities.push_back(entity);
}

void SceneGraph::pushSurface(const Surface* surface)
{
	if (!surface)
	{
		gameLog.warning("Could not add null surface to scenegraph!");
		return;
	}
	_surfaces.push_back(surface);
}

const Entity* SceneGraph::getEntity(unsigned int index) const
{
	if (_entities.size() < index + 1)
	{
		return nullptr;
	}
	return _entities[index];
}

const Surface* SceneGraph::getSurface(unsigned int index) const
{
	if (_surfaces.size() < index + 1)
	{
		return nullptr;
	}
	return _surfaces[index];
}