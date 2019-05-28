#include "renderer.h"
#include "../../defs.h"

Renderer::Renderer(int width, int height, const std::string& title)
	: _win(width, height, title.c_str())
{
	initRenderables(this);
	_renderables.reserve(500);
}

Renderer::~Renderer()
{
	destroyRenderables();
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
	_win.clear();
	for (auto& renderable : _renderables)
	{
		renderable->render(Vec2(0, 0));
		if (!renderable->isStreaming())
		{
			renderable->destroy();
		}
	}
	_win.update();
	_renderables.clear();
}