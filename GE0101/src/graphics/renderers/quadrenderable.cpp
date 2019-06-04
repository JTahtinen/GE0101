#include "quadrenderable.h"
#include "../../defs.h"
#include "renderer.h"
#include "../buffers/vertexarray.h"
#include "../shader.h"

static VertexArray* quadVao;
static Buffer*		quadVbo;
static Shader*		quadShader;

static QuadRenderable*	quadRenderablePool;

static std::vector<unsigned int>	availableQuadRenderables;

void QuadRenderable::init(const Renderer* renderer)
{
	quadRenderablePool = new QuadRenderable[RENDERABLE_POOL_SIZE];


	for (unsigned int i = 0; i < RENDERABLE_POOL_SIZE; ++i)
	{
		availableQuadRenderables.push_back(i);
	}




	quadShader = new Shader("res/shaders/colorquad", true);
	quadShader->bind();
	//quadShader->setUniform1f("u_ScreenRatio", renderer->getDisplayRatio());
	//quadVao = new VertexArray("quadVertices");
	quadVao->bind();
	quadVbo = new Buffer();
	quadVbo->bind();
	float quadPos[] = { 0, 0 };
	quadVbo->push(&quadPos[0], sizeof(Vec2));
	BufferLayout quadLayout;
	quadLayout.push<float>(2);
	quadVao->push(quadVbo, quadLayout);
}

void QuadRenderable::quit()
{
	delete quadVao;
	delete quadShader;

	quadVao = nullptr;
	quadShader = nullptr;

	delete[] quadRenderablePool;

	quadRenderablePool = nullptr;
}

QuadRenderable::QuadRenderable(const Vec4& pos, const Vec2& dimensions, const Vec4& color, bool streaming)
	: _dimensions(dimensions)
	, _color(color)
	, Renderable(pos, streaming)
{
}

QuadRenderable::QuadRenderable(const Vec4& pos, const Vec2& dimensions, bool streaming)
	: QuadRenderable(pos, dimensions, Vec4(0.8f, 0.8f, 0.8f, 1.0f), streaming)
{
}

QuadRenderable* QuadRenderable::createQuadRenderable(const Vec4& pos, const Vec2& dimensions, const Vec4& color, bool streaming)
{
	unsigned int tag;
	QuadRenderable* renderable = createRenderable(quadRenderablePool, availableQuadRenderables, &tag);
	if (!renderable)
	{
		ERR("Could not create quad renderable - Limit reached!");
		return nullptr;
	}
	*renderable = QuadRenderable(pos, dimensions, color, streaming);
	renderable->setTag(tag);
	return renderable;

}


QuadRenderable* QuadRenderable::createQuadRenderable(const Vec4& pos, const Vec2& dimensions, bool streaming)
{
	return createQuadRenderable(pos, dimensions, Vec4(0.8f, 0.8f, 0.8f, 1.0f), streaming);
}

void QuadRenderable::render(const Vec2& offset) const
{
	quadShader->bind();
	quadVao->bind();
	quadShader->setUniform2f("u_Dimensions", _dimensions.x, _dimensions.y);
	quadShader->setUniform2f("u_Position", _pos.x + offset.x, _pos.y + offset.y);
	quadShader->setUniform4f("u_Color", _color.x, _color.y, _color.z, _color.w);
	GLCALL(glDrawArrays(GL_POINTS, 0, 1));

	RENDER_CHILDREN();
}

void QuadRenderable::destroy()
{
	availableQuadRenderables.push_back(_tag);
	DESTROY_CHILDREN();
}