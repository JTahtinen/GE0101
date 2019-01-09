#pragma once
#include <vector>
#include "renderable.h"
#include "window.h"
#include "graphics.h"
#include "../game/camera.h"
#include "../game/entity.h"

class Renderer
{
	Window*								_target;
	Graphics*							_graphics;
	std::vector<const Entity*>			_renderables;
	const Camera*						_camera;
public:
	Renderer(Window* target, Graphics* graphics);
	void submit(const Entity* renderable);
	void flush();
};