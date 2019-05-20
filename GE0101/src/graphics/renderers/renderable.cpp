#include "renderable.h"
#include "../../defs.h"
#include "../../globals.h"

#define RENDER_CHILDREN() for (auto& child : _children) { if (child) {child->render();} }
#define RENDERABLE_POOL_SIZE 100

static VertexArray* textVao;
static Buffer*		textVbo;
static Shader*		textShader;

static VertexArray* quadVao;
static Buffer*		quadVbo;
static Shader*		quadShader;


static Renderable2D*	renderable2DPool[RENDERABLE_POOL_SIZE];
static TextRenderable*	textRenderablePool[RENDERABLE_POOL_SIZE];
static QuadRenderable*	quadRenderablePool[RENDERABLE_POOL_SIZE];

static std::vector<unsigned int>	availableRenderable2Ds;
static std::vector<unsigned int>	availableTextRenderables;
static std::vector<unsigned int>	availableQuadRenderables;

void initRenderables()
{
	for (unsigned int i = 0; i < RENDERABLE_POOL_SIZE; ++i)
	{
		renderable2DPool[i] = new Renderable2D(nullptr, nullptr, nullptr, Vec2());
		textRenderablePool[i] = new TextRenderable("", nullptr, Vec2());
		quadRenderablePool[i] = new QuadRenderable(Vec2(), Vec2());



		availableRenderable2Ds.push_back(i);
		availableTextRenderables.push_back(i);
		availableQuadRenderables.push_back(i);

	}

	textVao = new VertexArray();
	textVao->bind();
	textVbo = new Buffer();
	textVbo->bind();
	float textPos[] = { 0, 0 };
	textVbo->push(&textPos[0], sizeof(Vec2));
	BufferLayout textLayout;
	textLayout.push<float>(2);
	textVao->push(textVbo, textLayout);
	textShader = new Shader("res/shaders/letter", true);
	quadShader = new Shader("res/shaders/colorquad", true);
	quadVao = new VertexArray();
	quadVao->bind();
	quadVbo = new Buffer();
	quadVbo->bind();
	float quadPos[] = { 0, 0 };
	quadVbo->push(&quadPos[0], sizeof(Vec2));
	BufferLayout quadLayout;
	quadLayout.push<float>(2);
	quadVao->push(quadVbo, quadLayout);
}

void destroyRenderables()
{
	delete textVao;
	delete textShader;
	delete quadVao;
	delete quadShader;

	for (unsigned int i = 0; i < RENDERABLE_POOL_SIZE; ++i)
	{
		delete renderable2DPool[i];
		delete textRenderablePool[i];
		delete quadRenderablePool[i];

		renderable2DPool[i] = nullptr;
		textRenderablePool[i] = nullptr;
		quadRenderablePool[i] = nullptr;
	}
}


Renderable::Renderable(const Vec2& pos)
	: _pos(pos)
{
	_children.reserve(20);
}

void Renderable::addChild(Renderable* child)
{
	if (!child)
	{
		WARN("Could not add child for renderable - nullptr exception");
		return;
	}
	_children.push_back(child);
}

void Renderable::setTag(unsigned int tag)
{
	_tag = tag;
}

Renderable2D::Renderable2D(const VertexArray* vao, const IndexBuffer* ibo, const Texture* texture, const Vec2& pos)
	: _vao(vao)
	, _ibo(ibo)
	, _texture(texture)
	, Renderable(pos)
{
	static unsigned int num_renderable2D_ids = 0;
}


Renderable2D* Renderable2D::createRenderable2D(const VertexArray* vao, const IndexBuffer* ibo, const Texture* texture, const Vec2& pos)
{
	if (!availableRenderable2Ds.empty())
	{
		unsigned int i = availableRenderable2Ds.back();
		availableRenderable2Ds.pop_back();
		*renderable2DPool[i] = Renderable2D(vao, ibo, texture, pos);
		Renderable2D* renderable = renderable2DPool[i];
		renderable->setTag(i);
		return renderable;
	}
	ERR("Could not create renderable2D - Limit reached!");
	return nullptr;
}

Renderable2D* Renderable2D::createRenderable2D(const Sprite* sprite, const Vec2& pos)
{
	return createRenderable2D(sprite->vao, sprite->indices, sprite->texture, pos);
}

void Renderable2D::render() const
{
	basicShader->bind();
	basicShader->setUniform2f("u_Offset", _pos.x, _pos.y);
	_vao->bind();
	_ibo->bind();
	_texture->bind();
	glDrawElements(GL_TRIANGLES, _ibo->getSize(), GL_UNSIGNED_INT, NULL);

	RENDER_CHILDREN();
}

void Renderable2D::destroy()
{
	availableRenderable2Ds.push_back(_tag);
	for (auto& child : _children)
	{
		child->destroy();
	}
	_children.clear();
}

TextRenderable::TextRenderable(const std::string& text, const Font* font, const Vec2& pos)
	: Renderable(pos)
	, _font(font)
{
	if (_font)
	{
		_font->getAtlas()->bind(1);
	}
	_content.reserve(text.size());

	for (char c : text)
	{
		const Letter* letter = _font->getLetter(c);
		if (letter)
		{
			_content.push_back(letter);
		}
	}
}

TextRenderable* TextRenderable::createTextRenderable(const std::string& text, const Font* font, const Vec2& pos)
{
	if (!availableTextRenderables.empty())
	{
		unsigned int i = availableTextRenderables.back();
		availableTextRenderables.pop_back();
		*textRenderablePool[i] = TextRenderable(text, font, pos);
		TextRenderable* renderable = textRenderablePool[i];
		renderable->setTag(i);
		return renderable;
	}
	ERR("Could not create text renderable - Limit reached!");
	return nullptr;
}

void TextRenderable::render() const
{
	textShader->bind();
	textVao->bind();
	Vec2 cursor = _pos;
	for (auto& letter : _content)
	{
		textShader->setUniform2f("u_Position", cursor.x, cursor.y);
		textShader->setUniform2f("u_Dimensions", letter->width, letter->height);
		textShader->setUniform2f("u_Offset", letter->xOffset, letter->yOffset);
		textShader->setUniform2f("u_TexCoord", letter->x, letter->y);
		textShader->setUniform1i("u_Texture", 1);
		glDrawArrays(GL_POINTS, 0, 1);

		cursor.x += letter->xAdvance;
	}

	RENDER_CHILDREN();
}

void TextRenderable::destroy()
{
	availableTextRenderables.push_back(_tag);
	for (auto& child : _children)
	{
		child->destroy();
	}
	_children.clear();
}

QuadRenderable::QuadRenderable(const Vec2& pos, const Vec2& dimensions, const Vec4& color)
	: _dimensions(dimensions)
	, _color(color)
	, Renderable(pos)
{
}

QuadRenderable::QuadRenderable(const Vec2& pos, const Vec2& dimensions)
	: QuadRenderable(pos, dimensions, Vec4(0.8f, 0.8f, 0.8f, 1.0f))
{
}

QuadRenderable* QuadRenderable::createQuadRenderable(const Vec2& pos, const Vec2& dimensions, const Vec4& color)
{
	if (!availableQuadRenderables.empty())
	{
		unsigned int i = availableQuadRenderables.back();
		availableQuadRenderables.pop_back();
		*quadRenderablePool[i] = QuadRenderable(pos, dimensions, color);
		QuadRenderable* renderable = quadRenderablePool[i];
		renderable->setTag(i);
		return renderable;
	} 
	ERR("Could not create quad renderable - Limit reached!");
	return nullptr;
}
//
//QuadRenderable QuadRenderable::operator=(const QuadRenderable& other) const
//{
//	return QuadRenderable(other._pos, other._dimensions, other._color);
//}


QuadRenderable* QuadRenderable::createQuadRenderable(const Vec2& pos, const Vec2& dimensions)
{
	return createQuadRenderable(pos, dimensions, Vec4(0.8f, 0.8f, 0.8f, 1.0f));
}

void QuadRenderable::render() const
{
	quadShader->bind();
	quadVao->bind();
	quadShader->setUniform2f("u_Dimensions", _dimensions.x, _dimensions.y);
	quadShader->setUniform2f("u_Position", _pos.x, _pos.y);
	quadShader->setUniform4f("u_Color", _color.x, _color.y, _color.z, _color.w);
	glDrawArrays(GL_POINTS, 0, 1);

	RENDER_CHILDREN();
}

void QuadRenderable::destroy()
{
	availableQuadRenderables.push_back(_tag);
	for (auto& child : _children)
	{
		child->destroy();
	}
	_children.clear();
}