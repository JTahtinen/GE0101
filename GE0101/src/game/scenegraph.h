#pragma once
#include <vector>
#include "entity.h"

class SceneGraph
{
	std::vector<const Entity*>		_entities;
public:
	~SceneGraph();
	void pushEntity(const Entity* entity);
	const Entity* getEntity(unsigned int index) const;
	inline static SceneGraph& instance()
	{
		static SceneGraph graph;
		return graph;
	}
private:
	SceneGraph();
};