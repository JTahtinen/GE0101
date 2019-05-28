#pragma once
#include "../math/vec2.h"
#include "../graphics/renderers/renderer.h"
#include "font.h"
#include <vector>

class TextBox
{
	std::vector<std::string>	_lines;
	static const Font*			_font;
public:
	TextBox(const std::string& content);
	TextBox();
	inline static void setFont(const Font* font) { _font = font; }
	void setContent(const std::string& content);
	void pushContent(const std::string& content);
	void render(Renderer* Renderer, const Vec2& pos) const;
};