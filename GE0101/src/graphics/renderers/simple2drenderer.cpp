#include "simple2drenderer.h"
#include "GLEW/glew.h"
#include "../../defs.h"
#include "../buffers/vertexarray.h"

#define MAX_RENDERABLES 10
#define MAX_INDICES 6 * MAX_RENDERABLES

Simple2DRenderer::Simple2DRenderer()
{
	_renderables.reserve(MAX_RENDERABLES);
}

void Simple2DRenderer::submit(const Sprite* sprite, const Vec2& pos)
{
	if (!sprite)
	{
		WARN("Could not render sprite - nullptr!");
		return;
	}

	_renderables.push_back(Renderable{ sprite, pos});
}

void Simple2DRenderer::flush()
{
	for (auto& renderable : _renderables)
	{
		const Vec2& pos = renderable.pos;
		renderable.sprite->shader->setUniform2f("u_Offset", pos.x, pos.y);
		renderable.sprite->vbo->bind();
		renderable.sprite->indices->bind();
		renderable.sprite->texture->bind();
		glDrawElements(GL_TRIANGLES, renderable.sprite->indices->getSize(), GL_UNSIGNED_INT, NULL);
	}
	_renderables.clear();
}