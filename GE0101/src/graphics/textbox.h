#pragma once
#include "../math/vec2.h"
#include "../graphics/layer.h"
#include "font.h"
#include <vector>

class TextBox
{
	std::vector<std::string>					_lines;
	std::shared_ptr<const Font>					_font;
	Vec2										_dimensions;
	Vec4										_color;
	float										_textScale;
public:
	TextBox(const std::string& content, std::shared_ptr<const Font> font, float textScale = 0.5f);
	TextBox(std::shared_ptr<const Font> font);
	inline void setFont(std::shared_ptr<const Font> font) { if (font) _font = font; }
	void setContent(const std::string& content);
	void pushContent(const std::string& content);
	void setColor(const Vec4& color);
	void render(Layer& layer, const Vec2& pos) const;
};