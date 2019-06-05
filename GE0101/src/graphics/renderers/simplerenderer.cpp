/*#include "simplerenderer.h"
#include "../../defs.h"

SimpleRenderer::SimpleRenderer(Window* win)
	: Renderer(win)
{
	initRenderables(this);
	_renderables.reserve(500);
}

SimpleRenderer::~SimpleRenderer()
{
	destroyRenderables();
}

void SimpleRenderer::submit(const Sprite* renderable)
{
	if (!renderable)
	{
		WARN("Could not add renderable - nullptr exception");
		return;
	}

	//_renderables.push_back(renderable);
}

void SimpleRenderer::flush()
{
	clear();
	for (auto& renderable : _renderables)
	{
		renderable->render(Vec2(0, 0));
		if (!renderable->isStreaming())
		{
			destroyRenderable(renderable);
		}
	}
	update();
	_renderables.clear();
}*/