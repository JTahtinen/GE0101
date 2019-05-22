#include "renderer.h"
#include "../../defs.h"

Renderer::Renderer()
{
	_renderables.reserve(500);
}

void Renderer::submit(Renderable* renderable)
{
	if (!renderable)
	{
		WARN("Could not add renderable - nullptr exception");
		return;
	}

	_renderables.push_back(renderable);
}

void Renderer::flush()
{
	for (auto& renderable : _renderables)
	{
		renderable->render(Vec2(0, 0));
		if (!renderable->isStreaming())
		{
			renderable->destroy();
		}
	}
	_renderables.clear();
}