#include "renderer.h"
#include "../defs.h"
#include <iostream>

Renderer::Renderer(Window* target, Graphics* graphics)
	: _target(target)
	, _graphics(graphics)
{
	ASSERT(target);
	ASSERT(graphics);
	_renderables.reserve(100);
}

void Renderer::submit(const Renderable* renderable)
{
	if (renderable)
	{
		_renderables.push_back(renderable);
	}
}

void Renderer::flush()
{
	for (auto* renderable : _renderables)
	{
		const Vec2& pos = renderable->pos;
		//_graphics->drawRectAbsBordered(pos.x, pos.y, pos.x + 32, pos.y + 32, 0x00ff00);
		_graphics->drawSurfaceAbs(renderable->sprite, (int)pos.x, (int)pos.y, (int)pos.x + 32, (int)pos.y + 32);
	}
	_renderables.clear();
}
