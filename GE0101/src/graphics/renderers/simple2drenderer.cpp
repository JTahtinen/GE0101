#include "simple2drenderer.h"
#include "GLEW/glew.h"
#include "../../defs.h"
#include "../buffers/vertexarray.h"

#define MAX_RENDERABLES 100

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

	submit(sprite->vbo, sprite->indices, sprite->texture, pos);
}

void Simple2DRenderer::submit(const Buffer* vbo, const IndexBuffer* ibo, const Texture* texture, const Vec2& pos)
{
	if (vbo && ibo && texture && _shader)
	{
		_renderables.push_back(Renderable{ vbo, ibo, texture, pos });
	}
}

void Simple2DRenderer::flush()
{
	for (auto& renderable : _renderables)
	{
		const Vec2& pos = renderable.pos;
		_shader->setUniform2f("u_Offset", pos.x, pos.y);
		renderable.vbo->bind();
		renderable.ibo->bind();
		renderable.texture->bind();
		glDrawElements(GL_TRIANGLES, renderable.ibo->getSize(), GL_UNSIGNED_INT, NULL);
	}
	_renderables.clear();
}