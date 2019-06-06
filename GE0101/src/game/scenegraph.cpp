#include "scenegraph.h"
#include "../globals.h"

SceneGraph::SceneGraph()
{
	_entities.reserve(100);
}

SceneGraph::~SceneGraph()
{
}

void SceneGraph::pushEntity(std::shared_ptr<const Entity> entity)
{
	if (!entity)
	{
		gameLog.warning("Could not add null entity to scenegraph!");
	}
	_entities.push_back(entity);
}