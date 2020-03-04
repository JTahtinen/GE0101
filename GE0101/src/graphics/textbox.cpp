#include "textbox.h"
#include "../defs.h"

#define TEXTBOX_WIDTH_MARGIN (0.02f * _textScale)
#define TEXTBOX_HEIGHT_MARGIN (0.04f * _textScale)


TextBox::TextBox(const std::string& content, float textScale)
	: _dimensions(TEXTBOX_WIDTH_MARGIN, TEXTBOX_HEIGHT_MARGIN)
	, _color(Vec4(0.65f, 0.62f, 0.2f, 0.6f))
	, _textScale(textScale)
{
	if (_textScale < 0.001f)
	{
		_textScale = 0.001f;
	}
	_lines.reserve(10);
	if (content != "")
	{
		setContent(content);
	}
}

TextBox::TextBox()
	: TextBox("")
{
}

void TextBox::setContent(const std::string& content)
{
	clearContent();
	addContent(content);
}

void TextBox::addContent(const std::string& content)
{
	if (content != "")
	{
		_lines.emplace_back(Label(content, _textScale));
		calculateDimensions();
	}
}

void TextBox::setScale(const float scale)
{
	if (scale != _textScale)
	{
		if (scale < 0.01f)
		{
			_textScale = 0.01f;
		}
		else
		{
			_textScale = scale;
		}
		for (auto& line : _lines)
		{
			line.setScale(_textScale);
		}
		calculateDimensions();
	}
}

void TextBox::setColor(const Vec4& color)
{
	_color = color;
}

void TextBox::render(Layer& layer, const Vec2& pos) const
{
	Vec2 textOffset = Vec2(TEXTBOX_WIDTH_MARGIN * 0.5f, TEXTBOX_HEIGHT_MARGIN);

	layer.submitQuad(pos, Vec2(_dimensions.x, _dimensions.y), _color);
	for (int i = _lines.size() - 1; i > -1; --i)
	{
		const Label& line = _lines[i];
		_lines[i].render(pos + textOffset, layer);
		textOffset.y += line.getScreenDimensions().y;
	}
}

void TextBox::clearContent()
{
	_lines.clear();
	_dimensions = Vec2(TEXTBOX_WIDTH_MARGIN, TEXTBOX_HEIGHT_MARGIN);
}

void TextBox::calculateDimensions()
{
	Vec2 newDimensions(0, 0);
	for (auto& line : _lines)
	{
		const Vec2& lineDim = line.getScreenDimensions();
		if (lineDim.x > newDimensions.x)
		{
			newDimensions.x = lineDim.x;
		}
		newDimensions.y += lineDim.y;
	}
	_dimensions = Vec2(newDimensions.x + TEXTBOX_WIDTH_MARGIN, newDimensions.y + TEXTBOX_HEIGHT_MARGIN);
}