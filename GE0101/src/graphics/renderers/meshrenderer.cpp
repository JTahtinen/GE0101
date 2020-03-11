#include "meshrenderer.h"

struct VertexData
{
	Vec2 pos;
	Vec3 offset;
};

enum ShaderAttributeIndex
{
	SHADER_INDEX_POSITION = 0,
	SHADER_INDEX_OFFSET,
	SHADER_INDEX_AMT
};

#define RENDERER_MAX_TRIS 1000
#define RENDERER_VERTEX_SIZE sizeof(VertexData)
#define RENDERER_TRIANGLE_SIZE (RENDERER_VERTEX_SIZE * 3)
#define RENDERER_BUFFER_SIZE (RENDERER_TRIANGLE_SIZE * RENDERER_MAX_TRIS)

MeshRenderer::MeshRenderer(Window* win)
	: Renderer(win)
	, _shader("res/shaders/mesh")
{
	_shader.bind();
	_shader.setUniform4f("u_Color", 1.0f, 0.0f, 0.0f, 1.0f);
	_shader.setUniform1f("u_ScrRatio", win->getRatio());
	_batches.reserve(10);

	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);
	
	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(SHADER_INDEX_POSITION);
	glEnableVertexAttribArray(SHADER_INDEX_OFFSET);
	glVertexAttribPointer(SHADER_INDEX_POSITION, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const void*)0);
	glVertexAttribPointer(SHADER_INDEX_OFFSET, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const void*)(2 * sizeof(float)));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void MeshRenderer::submit(const Polygon& renderable, const Vec2& pos, const Vec3& offset)
{
	if (_batches.size() == 0)
	{
		_batches.emplace_back(PolygonBatch());
	}
	_batches.back().submit(renderable, pos);
}

void MeshRenderer::flush()
{
	_shader.bind();
	glBindVertexArray(_vao);
	for (const PolygonBatch& batch : _batches)
	{
		IndexBuffer ibo;
		ibo.bind();
		const std::vector<PolygonRenderable>& renderables = batch.getData();
		
		unsigned int numIndices = 0;
		unsigned int currentIndex = 0;
		unsigned int numPoints = 0;
		std::vector<const PolygonData*> polygons;
		for (const PolygonRenderable& renderable : renderables)
		{
			const PolygonData& polygonData = renderable.polygon.getData();
			numIndices += polygonData.indices.size();
			polygons.emplace_back(&polygonData);
		}
		std::vector<unsigned int> indices(numIndices);
		
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);

		_buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		for (const PolygonData* polygon : polygons)
		{
			for (unsigned int i = 0; i < polygon->points.size(); ++i)
			{
				_buffer->pos = polygon->points[i];
				_buffer->offset = Vec3(0, 0, 0);
				++_buffer;
			}
			const std::vector<unsigned int>& curPolyIndices = polygon->indices;
			for (unsigned int i = 0; i < curPolyIndices.size(); ++i)
			{
				indices[currentIndex + i] = (curPolyIndices[i] + numPoints);
			}
			numPoints += polygon->points.size();
			currentIndex += curPolyIndices.size();
		}
		ibo.push(&indices[0], indices.size());
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, NULL);
	}

	for (PolygonBatch& batch : _batches)
	{
		batch.clear();
	}
}