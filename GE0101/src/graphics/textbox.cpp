#include "textbox.h"
#include "../defs.h"

TextBox::TextBox(const std::string& content, const Font* font)
	: _content(content)
	, _font(font)
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
	static Vec2 textOffset = Vec2(0.02f, 0.13f);
	if (!renderer)
	{
		ERR("Could not render text box - Renderer was nullpt");
		return;
	}

	// Test values
	QuadRenderable* background =
	QuadRenderable::createQuadRenderable(pos, Vec2(0.4f, 0.15f), Vec4(0.65f, 0.62f, 0.0f, 1.0f));
	//TextRenderable* fg = TextRenderable::createTextRenderable(_content, _font, pos + _offset + textOffset);
	background->addChild(TextRenderable::createTextRenderable(_content, _font, textOffset, 0.5f));
	renderer->submit(background);
	//renderer->submit(fg);
}