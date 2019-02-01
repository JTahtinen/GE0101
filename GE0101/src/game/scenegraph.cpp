#include "scenegraph.h"
#include "../globals.h"

SceneGraph::SceneGraph()
{
	_entities.reserve(100);
}

SceneGraph::~SceneGraph()
{
	for (auto* entity : _entities)
	{
		delete entity;
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


const Entity* SceneGraph::getEntity(unsigned int index) const
{
	if (_entities.size() < index + 1)
	{
		return nullptr;
	}
	return _entities[index];
}