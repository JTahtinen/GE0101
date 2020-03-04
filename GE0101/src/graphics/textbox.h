#pragma once
#include "../math/vec2.h"
#include "../graphics/layer.h"
#include "label.h"
#include <vector>

class TextBox
{
	std::vector<Label>							_lines;
	Vec2										_dimensions;
	Vec4										_color;
	float										_textScale;
public:
	TextBox(const std::string& content, float textScale = 0.5f);
	TextBox();
	void setContent(const std::string& content);
	void addContent(const std::string& content);
	void setScale(const float scale);
	void setColor(const Vec4& color);
	void render(Layer& layer, const Vec2& pos) const;
private:
	void clearContent();
	void calculateDimensions();
};