#pragma once

#include <vector>
#include "renderable.h"

class Renderer 
{
	std::vector<Renderable*>	_renderables;
public:
	Renderer();
	void submit(Renderable* renderable);
	void flush();
};
