#include "textbox.h"
#include "../defs.h"

std::weak_ptr<const Font> TextBox::s_defaultFont;

TextBox::TextBox(const std::string& content, float textScale)
	: _dimensions(0.1f, 0.1f)
	, _textScale(textScale)
	, _color(Vec4(0.65f, 0.62f, 0.2f, 0.6f))
{
	setFont(std::shared_ptr<const Font>(s_defaultFont));
	_lines.reserve(10);
	if (content != "")
	{
		setContent(content);
	}
	const auto& letter = _font->getLetter(' ');
}

TextBox::TextBox()
	: TextBox("")
{
}

void TextBox::setDefaultFont(std::shared_ptr<const Font>(font))
{
	s_defaultFont = font;
}

void TextBox::setContent(const std::string& content)
{
	_lines.clear();
	pushContent(content);
}

void TextBox::pushContent(const std::string& content)
{
	_lines.emplace_back(content);
	float lineWidth = 0.0f;
	for (auto& c : content)
	{
		const auto& letter = _font->getLetter(c);
		lineWidth += letter->xAdvance * _textScale;
	}
	if (lineWidth > _dimensions.x)
	{
		_dimensions.x = lineWidth;
	}

	_dimensions.y = _lines.size() * 0.2f * _textScale;
}

void TextBox::setColor(const Vec4& color)
{
	_color = color;
}

void TextBox::render(Layer& layer, const Vec2& pos) const
{
	Vec2 textOffset = Vec2(0.02f, 0.015f);
	

	// Test values
	layer.submitQuad(pos, Vec2(_dimensions.x + textOffset.x * 2.0f, _dimensions.y), _color);
	//QuadRenderable* background =
	//QuadRenderable::createQuadRenderable(Vec4(pos.x, pos.y, 0, 0), Vec2(_dimensions.x + textOffset.x * 2.0f, _dimensions.y), _color);
	//TextRenderable* fg = TextRenderable::createTextRenderable(_content, _font, pos + _offset + textOffset);
	for (auto& line : _lines)
	{
		//background->addChild(TextRenderable::createTextRenderable(line, _font, Vec4(textOffset.x, textOffset.y, 0, 0), _textScale));
		layer.submitText(line, pos + textOffset, _textScale, _font);
		textOffset.y -= 0.2f * _textScale;
	}
	//layer->submitQuad(background);
	//renderer->submit(fg);
}