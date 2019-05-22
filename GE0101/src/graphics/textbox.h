#pragma once
#include "../math/vec2.h"
#include "../graphics/renderers/renderer.h"
#include "font.h"

class TextBox
{
	std::string		_content;
	const Font*		_font;
public:
	TextBox(const std::string& content, const Font* font);
	TextBox(const Font* font);
	void setContent(const std::string& content);
	void render(Renderer* Renderer, const Vec2& pos) const;
};