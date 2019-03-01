#include "simple2drenderer.h"
#include "GLEW/glew.h"
#include "../../defs.h"
#include "../buffers/vertexarray.h"

#define MAX_RENDERABLES 10
#define MAX_INDICES 6 * MAX_RENDERABLES

Simple2DRenderer::Simple2DRenderer()
{
	_renderables.reserve(MAX_RENDERABLES);
	_indices.reserve(MAX_INDICES);
	_indices.push_back(0);
	_indices.push_back(1);
	_indices.push_back(2);
	_indices.push_back(2);
	_indices.push_back(0);
	_indices.push_back(3);
	glBufferData
	(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned int), &_indices[0], GL_STATIC_DRAW);
}

void Simple2DRenderer::submit(const Renderable* renderable)
{
	if (!renderable)
	{
		WARN("Could not submit renderable to renderer - nullptr!");
		return;
	}

	_renderables.push_back(renderable);
}

void Simple2DRenderer::flush()
{
	for (auto& renderable : _renderables)
	{
		const Vec2& pos = renderable->pos;
		const Vec2& dim = renderable->sprite->_dimensions;
		renderable->shader->setUniform2f("u_Offset", pos.x, pos.y);
		renderable->data->bind();
		renderable->indices->bind();
		//glBufferData(GL_ARRAY_BUFFER, sizeof(Vec2) * 4, &vertices[0], GL_STATIC_DRAW);
		renderable->sprite->_texture.bind();
		glDrawElements(GL_TRIANGLES, renderable->indices->getSize(), GL_UNSIGNED_INT, NULL);
	}
	_renderables.clear();
}