#include "textbox.h"
#include "../defs.h"

const Font* TextBox::_font;

TextBox::TextBox(const std::string& content)
{
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
	_lines.clear();
	_lines.emplace_back(content);
}

void TextBox::pushContent(const std::string& content)
{
	_lines.emplace_back(content);
}

void TextBox::render(Renderer* renderer, const Vec2& pos) const
{
	Vec2 textOffset = Vec2(0.02f, 0.13f);
	if (!renderer)
	{
		ERR("Could not render text box - Renderer was nullpt");
		return;
	}

	// Test values
	QuadRenderable* background =
	QuadRenderable::createQuadRenderable(pos, Vec2(0.4f, _lines.size() * 0.2f), Vec4(0.65f, 0.62f, 0.0f, 1.0f));
	//TextRenderable* fg = TextRenderable::createTextRenderable(_content, _font, pos + _offset + textOffset);
	for (auto& line : _lines)
	{
		background->addChild(TextRenderable::createTextRenderable(line, _font, textOffset, 0.5f));
		textOffset.y -= 0.1f;
	}
	renderer->submit(background);
	//renderer->submit(fg);
}