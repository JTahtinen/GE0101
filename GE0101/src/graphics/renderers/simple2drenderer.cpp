#include "simple2drenderer.h"
#include "GLEW/glew.h"
#include "../../defs.h"
#include "../buffers/vertexarray.h"


void Simple2DRenderer::submit(const Sprite* sprite, const Vec2& pos)
{
	if (!sprite)
	{
		WARN("Could not render sprite - nullptr!");
		return;
	}

	submit(sprite->vao, sprite->indices, sprite->texture, pos);
}

void Simple2DRenderer::submit(const VertexArray* vao, const IndexBuffer* ibo, const Texture* texture, const Vec2& pos)
{
	if (vao && ibo && texture && _shader)
	{
		_renderables.push_back(Renderable{ vao, ibo, texture, pos });
	}
}

