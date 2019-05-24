#include "renderable.h"
#include "../../defs.h"
#include "../../globals.h"
#include "../buffers/vertexarray.h"

#define RENDER_CHILDREN() for (auto& child : _children) { if (child) {child->render(_pos + offset);} }
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

template <typename T>
T* createRenderable(T* pool[], std::vector<unsigned int>& availableRenderables, unsigned int* tag)
{
	if (!availableRenderables.empty())
	{
		unsigned int i = availableRenderables.back();
		availableRenderables.pop_back();
		//*pool[i] = T(vao, ibo, texture, pos);
		T* renderable = pool[i];
		*tag = i;
		return renderable;
	}
	return nullptr;
}
void initRenderables()
{
	for (unsigned int i = 0; i < RENDERABLE_POOL_SIZE; ++i)
	{
		renderable2DPool[i] = new Renderable2D(nullptr, Vec2(), 0.0f);
		textRenderablePool[i] = new TextRenderable("", nullptr, Vec2(), 0.0f);
		quadRenderablePool[i] = new QuadRenderable(Vec2(), Vec2());



		availableRenderable2Ds.push_back(i);
		availableTextRenderables.push_back(i);
		availableQuadRenderables.push_back(i);

	}

	textVao = new VertexArray("textVertices");
	textVao->bind();
	textVbo = new Buffer();
	textVbo->bind();
	float textPos[] = { 0, 0 };
	textVbo->push(&textPos[0], sizeof(Vec2));
	BufferLayout textLayout;
	textLayout.push<float>(2);
	textVao->push(textVbo, textLayout);
	textShader = new Shader("res/shaders/letter", true);
	textShader->bind();
	textShader->setUniform1f("u_ScreenRatio", 16.0f / 9.0f);
	textShader->setUniform1f("u_Scale", 0.3f);
	quadShader = new Shader("res/shaders/colorquad", true);
	quadShader->bind();
	quadShader->setUniform1f("u_ScreenRatio", 16.0f / 9.0f);
	quadVao = new VertexArray("quadVertices");
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


Renderable::Renderable(const Vec2& pos, bool streaming)
	: _pos(pos)
	, _streaming(streaming)
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

void Renderable::freeRenderable()
{
	_streaming = false;
}

Renderable2D::Renderable2D(const Sprite* sprite, const Vec2& pos, float scale, bool streaming)
	: 
	_sprite(sprite)
	, _scale(scale)
	, Renderable(pos, streaming)
{
}


Renderable2D* Renderable2D::createRenderable2D(const Sprite* sprite, const Vec2& pos, float scale, bool streaming)
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
	basicShader->setUniform2f("u_Offset", _pos.x + offset.x, _pos.y + offset.y);
	basicShader->setUniform1f("u_Scale", _scale);
	basicShader->setUniform1i("u_Texture", 0);
	GLCALL(glDrawElements(GL_TRIANGLES, _sprite->getElementCount(), GL_UNSIGNED_INT, NULL));

	RENDER_CHILDREN();
}

void Renderable2D::destroy()
{
	availableRenderable2Ds.push_back(_tag);
	for (auto& child : _children)
	{
		if (!child->isStreaming())
		{
			child->destroy();
		}
	}
	_children.clear();
}

TextRenderable::TextRenderable(const std::string& text, const Font* font, const Vec2& pos, float scale, bool streaming)
	: Renderable(pos, streaming)
	, _scale(scale)
{
	setFont(font);
	setContent(text);
}

TextRenderable* TextRenderable::createTextRenderable(const std::string& text, const Font* font, const Vec2& pos, float scale, bool streaming)
{
	unsigned int tag;
	TextRenderable* renderable = createRenderable(textRenderablePool, availableTextRenderables, &tag);
	if (!renderable)
	{
		ERR("Could not create text renderable - Limit reached!");
		return nullptr;
	}
	*renderable = TextRenderable(text, font, pos, scale, streaming);
	renderable->setTag(tag);
	return renderable;
}

void TextRenderable::render(const Vec2& offset) const
{
	textShader->bind();
	textVao->bind();
	textShader->setUniform1f("u_Scale", _scale);
	Vec2 cursor = _pos + offset;
	for (auto& letter : _content)
	{
		textShader->setUniform2f("u_Position", cursor.x, cursor.y);
		textShader->setUniform2f("u_Dimensions", letter->width, letter->height);
		textShader->setUniform2f("u_Offset", letter->xOffset, letter->yOffset);
		textShader->setUniform2f("u_TexCoord", letter->x, letter->y);
		textShader->setUniform1i("u_Texture", 1);
		GLCALL(glDrawArrays(GL_POINTS, 0, 1));

		cursor.x += letter->xAdvance * _scale;
	}

	RENDER_CHILDREN();
}

void TextRenderable::setContent(const std::string& text)
{
	_content.clear();
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

void TextRenderable::setFont(const Font* font)
{
	if (!font)
	{
		ERR("Could not set font - nullptr exception");
		return;
	}
	_font = font;
	_font->getAtlas()->bind(1);
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

QuadRenderable::QuadRenderable(const Vec2& pos, const Vec2& dimensions, const Vec4& color, bool streaming)
	: _dimensions(dimensions)
	, _color(color)
	, Renderable(pos, streaming)
{
}

QuadRenderable::QuadRenderable(const Vec2& pos, const Vec2& dimensions, bool streaming)
	: QuadRenderable(pos, dimensions, Vec4(0.8f, 0.8f, 0.8f, 1.0f), streaming)
{
}

QuadRenderable* QuadRenderable::createQuadRenderable(const Vec2& pos, const Vec2& dimensions, const Vec4& color, bool streaming)
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


QuadRenderable* QuadRenderable::createQuadRenderable(const Vec2& pos, const Vec2& dimensions, bool streaming)
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
	for (auto& child : _children)
	{
		child->destroy();
	}
	_children.clear();
}