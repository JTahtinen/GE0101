/*#include "textrenderable.h"
#include "../../defs.h"
#include "../buffers/vertexarray.h"
#include "../shader.h"
#include "renderer.h"

static VertexArray* textVao;
static Buffer*		textVbo;
static Shader*		textShader;

static TextRenderable*	textRenderablePool;
static std::vector<unsigned int>	availableTextRenderables;

void TextRenderable::init(const Renderer *renderer)
{
	textRenderablePool = new TextRenderable[RENDERABLE_POOL_SIZE];
	for (unsigned int i = 0; i < RENDERABLE_POOL_SIZE; ++i)
	{
		availableTextRenderables.push_back(i);
	}
	//textVao = new VertexArray("textVertices");
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
	//textShader->setUniform1f("u_ScreenRatio", renderer->getDisplayRatio());
	textShader->setUniform1f("u_Scale", 0.1f);
}

void TextRenderable::quit()
{
	delete textVao;
	delete textShader;
	textVao = nullptr;
	textShader = nullptr;
	delete[] textRenderablePool;
	textRenderablePool = nullptr;
}

TextRenderable::TextRenderable(const std::string& text, const Font* font, const Vec4& pos, float scale, bool streaming)
	: Renderable(pos, streaming)
	, _scale(scale)
{
	setFont(font);
	setContent(text);
}

TextRenderable* TextRenderable::createTextRenderable(const std::string& text, const Font* font, const Vec4& pos, float scale, bool streaming)
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
	_font->bind();
	Vec4 cursor = _pos + Vec4(offset.x, offset.y, 0, 1);
	for (auto& letter : _content)
	{
		textShader->setUniform2f("u_Position", cursor.x, cursor.y);
		textShader->setUniform2f("u_Dimensions", letter->width, letter->height);
		textShader->setUniform2f("u_Offset", letter->xOffset, letter->yOffset);
		textShader->setUniform2f("u_TexCoord", letter->x, letter->y);
		textShader->setUniform1i("u_Texture", TEXTURE_SLOT_FONT_ATLAS);
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
		//ERR("Could not set font - nullptr exception");
		return;
	}
	_font = font;
	//_font->getAtlas()->bind(TEXTURE_SLOT_FONT_ATLAS);
}

void TextRenderable::destroy()
{
	availableTextRenderables.push_back(_tag);
	DESTROY_CHILDREN();
}*/