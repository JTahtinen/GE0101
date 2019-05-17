#include "textrenderer.h"

static VertexArray*	_vao;
static Buffer*		_vbo;

TextRenderer::TextRenderer(const Font* font)
	: _font(font)
{
	setShader(new Shader("res/shaders/letter", true));
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
	font->getAtlas()->bind(1);
	_renderables.reserve(500);
}

void TextRenderer::setFont(const Font* font)
{
	_font = font;
	if (_font)
	{
		ERR("Could not set font for text renderer - nullptr exception");
	}
}

void TextRenderer::submit(const std::string& text, const Vec2& pos)
{
	if (!_font)
	{
		ERR("Could not render text - Font not loaded");
		return;
	}
	_cursor = pos;
	for (unsigned int i = 0; i < text.size(); ++i)
	{
		const Letter* letter = _font->getLetter(text[i]);
		if (letter)
		{
			
			_renderables.push_back(_font->getLetter(text[i]));
		}
	}
}

void TextRenderer::flush()
{
	_shader->bind();
	_vao->bind();
	for (auto& renderable : _renderables)
	{
		_shader->setUniform2f("u_Position", _cursor.x, _cursor.y);
		_shader->setUniform2f("u_Dimensions", renderable->width, renderable->height);
		_shader->setUniform2f("u_Offset", renderable->xOffset, renderable->yOffset);
		_shader->setUniform2f("u_TexCoord", renderable->x, renderable->y);
		_shader->setUniform1i("u_Texture", 1);
		glDrawArrays(GL_POINTS, 0, 1);
		
		_cursor.x += renderable->xAdvance;

	}
	_renderables.clear();
}