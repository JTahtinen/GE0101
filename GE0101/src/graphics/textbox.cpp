#include "textbox.h"
#include "../defs.h"

const Font* TextBox::_defaultFont;

TextBox::TextBox(const std::string& content, float textScale)
	: _dimensions(0.1f, 0.1f)
	, _textScale(textScale)
	, _color(Vec4(0.65f, 0.62f, 0.2f, 1.0f))
{
	setFont(_defaultFont);
	_lines.reserve(10);
	if (content != "")
	{
		setContent(content);
	}
	const Letter* letter = _font->getLetter(' ');
}

TextBox::TextBox()
	: TextBox("")
{
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
		const Letter* letter = _font->getLetter(c);
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

void TextBox::render(Renderer* renderer, const Vec2& pos) const
{
	Vec2 textOffset = Vec2(0.02f, 0.0f);
	if (!renderer)
	{
		ERR("Could not render text box - Renderer was nullpt");
		return;
	}

	// Test values
	QuadRenderable* background =
	QuadRenderable::createQuadRenderable(Vec4(pos.x, pos.y, 0, 0), Vec2(_dimensions.x + textOffset.x * 2.0f, _dimensions.y), _color);
	//TextRenderable* fg = TextRenderable::createTextRenderable(_content, _font, pos + _offset + textOffset);
	for (auto& line : _lines)
	{
		background->addChild(TextRenderable::createTextRenderable(line, _font, Vec4(textOffset.x, textOffset.y, 0, 0), _textScale));
		textOffset.y -= 0.2f * _textScale;
	}
	renderer->submit(background);
	//renderer->submit(fg);
}