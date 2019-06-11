#include "quadrenderer.h"
#include "../shader.h"
#include "../../defs.h"

static Shader* quadShader;

struct QuadData
{
	Vec2 pos;
	Vec2 size;
	Vec4 color;
};


enum ShaderAttributeIndex
{
	SHADER_INDEX_POSITION = 0,
	SHADER_INDEX_SIZE,
	SHADER_INDEX_COLOR,
	SHADER_INDEX_AMT
};

#define RENDERER_MAX_QUADS 60000
#define RENDERER_QUAD_SIZE sizeof(QuadData)
#define RENDERER_BUFFER_SIZE (RENDERER_QUAD_SIZE * RENDERER_MAX_QUADS)


QuadRenderer::QuadRenderer(Window* win)
	: Renderer(win)
{
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);
	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(SHADER_INDEX_POSITION);
	glEnableVertexAttribArray(SHADER_INDEX_SIZE);
	glEnableVertexAttribArray(SHADER_INDEX_COLOR);
	glVertexAttribPointer(SHADER_INDEX_POSITION, 2, GL_FLOAT, GL_FALSE, RENDERER_QUAD_SIZE, (const void*)0);
	glVertexAttribPointer(SHADER_INDEX_SIZE, 2, GL_FLOAT, GL_FALSE, RENDERER_QUAD_SIZE, (const void*)(2 * sizeof(float)));
	glVertexAttribPointer(SHADER_INDEX_COLOR, 4, GL_FLOAT, GL_FALSE, RENDERER_QUAD_SIZE, (const void*)(4 * sizeof(float)));
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void QuadRenderer::submit(const Vec2& pos, const Vec2& size, const Vec4& color)
{
	_batch.submit(pos, size, color);
}

void QuadRenderer::flush()
{
	quadShader->bind();
	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	QuadData* buffer = (QuadData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	unsigned int numQuads = 0;
	const auto& data = _batch.getData();
	for (auto& quad : data)
	{
		const Vec2& pos = quad.pos;
		const Vec2& size = quad.size;
		const Vec4& color = quad.color;

		buffer->pos = pos;
		buffer->size = size;
		buffer->color = color;

		++buffer;
		++numQuads;
	}
	glUnmapBuffer(GL_ARRAY_BUFFER);
	_batch.clear();
	glDrawArrays(GL_POINTS, 0, numQuads);
}

void QuadRenderer::init(const Window& win)
{
	quadShader = new Shader("res/shaders/colorquad", true);
	quadShader->bind();
	quadShader->setUniform1f("u_ScreenRatio", win.getRatio());
}

void QuadRenderer::quit()
{
	delete quadShader;
	quadShader = nullptr;
}