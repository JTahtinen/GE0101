#pragma once
#include <vector>
#include "entity/entity.h"

class SceneGraph
{
	std::vector<std::shared_ptr<const Entity>>		_entities;
public:
	~SceneGraph();
	void pushEntity(std::shared_ptr<const Entity> entity);
	inline static SceneGraph& instance()
	{
		static SceneGraph graph;
		return graph;
	}
private:
	SceneGraph();
};