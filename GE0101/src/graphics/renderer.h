#pragma once
#include <vector>
#include "renderable.h"
#include "window.h"
#include "graphics.h"

class Renderer
{
	Window*								_target;
	Graphics*							_graphics;
	std::vector<const Renderable*>		_renderables;
public:
	Renderer(Window* target, Graphics* graphics);
	void submit(const Renderable* renderable);
	void flush();
};