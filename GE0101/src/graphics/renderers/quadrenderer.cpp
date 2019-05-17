#include "../buffers/vertexarray.h"
#include "quadrenderer.h"
#include "../../defs.h"

static VertexArray*	_vao;
static Buffer*		_vbo;

QuadRenderer::QuadRenderer()
{
	setShader(new Shader("res/shaders/colorquad", true));
	_vao = new VertexArray();
	_vao->bind();
	_vbo = new Buffer();
	_vbo->bind();
	float pos[] = { 0, 0 };
	_vbo->push(&pos[0], sizeof(Vec2));
	BufferLayout layout;
	layout.push<float>(2);
	_vao->push(_vbo, layout);
	ASSERT(_shader);
	_renderables.reserve(100);
}

QuadRenderer::~QuadRenderer()
{
	delete _vao;
	delete _vbo;
	_vao = nullptr;
	_vbo = nullptr;
}

void QuadRenderer::submit(const Vec2& pos, const Vec2& dimensions, const Vec4& color)
{
	_renderables.push_back({ pos, dimensions, color });
}

void QuadRenderer::flush()
{
	_shader->bind();
	_vao->bind();
	for (auto& renderable : _renderables)
	{
		const Vec2& pos = renderable.pos;
		const Vec2& dimensions = renderable.dimensions;
		const Vec4& color = renderable.color;
		_shader->setUniform2f("u_Dimensions", dimensions.x, dimensions.y);
		_shader->setUniform2f("u_Position", pos.x, pos.y);
		_shader->setUniform4f("u_Color", color.r, color.g, color.b, color.a);
		glDrawArrays(GL_POINTS, 0, 1);
	}
	_renderables.clear();
}