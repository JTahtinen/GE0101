#include "renderer2d.h"

#define MAX_RENDERABLES 100

Renderer2D::Renderer2D()
{
	_renderables.reserve(MAX_RENDERABLES);
}

void Renderer2D::flush()
{
	for (auto& renderable : _renderables)
	{
		const Vec2& pos = renderable.pos;
		_shader->bind();
		_shader->setUniform2f("u_Offset", pos.x, pos.y);
		renderable.vao->bind();
		renderable.ibo->bind();
		renderable.texture->bind();
		glDrawElements(GL_TRIANGLES, renderable.ibo->getSize(), GL_UNSIGNED_INT, NULL);
	}
	_renderables.clear();
}