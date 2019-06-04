#pragma once
#include "../math/vec2.h"
#include "../graphics/layer.h"
#include "font.h"
#include <vector>

class TextBox
{
	std::vector<std::string>	_lines;
	const Font*					_font;
	static const Font*			_defaultFont;
	Vec2						_dimensions;
	Vec4						_color;
	float						_textScale;
public:
	TextBox(const std::string& content, float textScale = 0.5f);
	TextBox();
	inline void setFont(const Font* font) { if (font) _font = font; }
	inline static void setDefaultFont(const Font* font) { _defaultFont = font; }
	void setContent(const std::string& content);
	void pushContent(const std::string& content);
	void setColor(const Vec4& color);
	void render(Layer* layer, const Vec2& pos) const;
};