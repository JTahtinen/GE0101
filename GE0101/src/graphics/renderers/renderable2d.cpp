#include "renderable2d.h"
#include "../../defs.h"
#include "renderer.h"
#include "../shader.h"

static Renderable2D*				renderable2DPool;
static std::vector<unsigned int>	availableRenderable2Ds;

static Shader*		basicShader;

void Renderable2D::init(const Renderer* renderer) 
{
	renderable2DPool = new Renderable2D[RENDERABLE_POOL_SIZE];
	for (unsigned int i = 0; i < RENDERABLE_POOL_SIZE; ++i)
	{
		availableRenderable2Ds.push_back(i);
	}
	basicShader = new Shader("res/shaders/basic");
	basicShader->bind();
	basicShader->setUniform4f("u_Color", 0, 0.0f, 0.1f, 0);
	basicShader->setUniform4f("u_Offset", 0, 0, 0, 1);
	basicShader->setUniform1f("u_ScrRatio", renderer->getDisplayRatio());
	basicShader->setUniform1f("u_Scale", 1.0f);
	basicShader->setUniform1i("u_Texture", TEXTURE_SLOT_SPRITE);
}

void Renderable2D::quit()
{
	delete[] renderable2DPool;
	renderable2DPool = nullptr;
	delete basicShader;
}


Renderable2D::Renderable2D(const Sprite* sprite, const Vec4& pos, float scale, bool streaming)
	:
	_sprite(sprite)
	, _scale(scale)
	, Renderable(pos, streaming)
{
}


Renderable2D* Renderable2D::createRenderable2D(const Sprite* sprite, const Vec4& pos, float scale, bool streaming)
{
	unsigned int tag;
	Renderable2D* renderable = createRenderable<Renderable2D>(renderable2DPool, availableRenderable2Ds, &tag);
	if (!renderable)
	{
		ERR("Could not create renderable2D - Limit reached!");
		return nullptr;
	}
	*renderable = Renderable2D(sprite, pos, scale, streaming);
	renderable->setTag(tag);
	return renderable;
}

void Renderable2D::render(const Vec2& offset) const
{
	basicShader->bind();
	_sprite->bind();
	basicShader->setUniform4f("u_Offset", _pos.x + offset.x, _pos.y + offset.y, _pos.z, _pos.w);
	basicShader->setUniform1f("u_Scale", _scale);
	basicShader->setUniform1i("u_Texture", TEXTURE_SLOT_SPRITE);
	GLCALL(glDrawElements(GL_TRIANGLES, _sprite->getElementCount(), GL_UNSIGNED_INT, NULL));

	RENDER_CHILDREN();
}

void Renderable2D::destroy()
{
	availableRenderable2Ds.push_back(_tag);
	DESTROY_CHILDREN();
}
