#pragma once
#include <vector>
#include "../graphics/surface.h"
#include "entity.h"

class SceneGraph
{
	std::vector<const Entity*>		_entities;
	std::vector<const Surface*>		_surfaces;
public:
	~SceneGraph();
	void pushEntity(const Entity* entity);
	void pushSurface(const Surface* surface);
	const Entity* getEntity(unsigned int index) const;
	const Surface* getSurface(unsigned int index) const;
	inline static SceneGraph& instance()
	{
		static SceneGraph graph;
		return graph;
	}
private:
	SceneGraph();
};