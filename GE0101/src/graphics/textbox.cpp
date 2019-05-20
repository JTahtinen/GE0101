#include "textbox.h"
#include "../defs.h"

TextBox::TextBox(const std::string& content, const Vec2& offset, const Font* font)
	: _content(content)
	, _offset(offset)
	, _font(font)
{

}

TextBox::TextBox(const std::string& content, const Font* font)
	: TextBox(content, Vec2(0, 0), font)
{

}

TextBox::TextBox(const Font* font)
	: TextBox("", font)
{
}

void TextBox::setContent(const std::string& content)
{
	_content = content;
}

void TextBox::render(Renderer* renderer, const Vec2& pos) const
{
	static Vec2 textOffset = Vec2(0.02f, 0.1f);
	if (!renderer)
	{
		ERR("Could not render text box - Renderer was nullpt");
		return;
	}

	// Test values
	QuadRenderable* background =
	QuadRenderable::createQuadRenderable(pos + _offset, Vec2(0.3f, 0.3f), Vec4(0.8f, 0.65f, 0.5f, 1.0f));
	//TextRenderable* fg = TextRenderable::createTextRenderable(_content, _font, pos + _offset + textOffset);
	background->addChild(TextRenderable::createTextRenderable(_content, _font, pos + _offset + textOffset));
	renderer->submit(background);
	//renderer->submit(fg);
}