#pragma once

#include <vector>
#include "../window.h"
#include <string>
#include "renderer.h"

class SimpleRenderer : public Renderer 
{
	std::vector<Renderable*>	_renderables;
public:
	SimpleRenderer(Window* win);
	~SimpleRenderer();
	void submit(const Sprite* renderable);
	virtual void flush() override;
};
