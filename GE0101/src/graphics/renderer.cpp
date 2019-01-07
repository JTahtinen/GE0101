#include "renderer.h"
#include "../defs.h"

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
		_graphics->drawRectAbsBordered(pos.x, pos.y, pos.x + 32, pos.y + 32, 0x00ff00);
	}
	_renderables.clear();
}