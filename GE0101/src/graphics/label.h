#pragma once
#include <string>
#include "font.h"
#include "../math/vec2.h"
#include "layer.h"

class Label
{
	std::string							_content;
	float								_scale;
	std::shared_ptr<const Font>			_font;
	float								_screenWidth;
	float								_screenHeight;
public:
	Label(const std::string& content, const float scale, std::shared_ptr<const Font> font);
	Label(const std::string& content, const float scale);
	void render(const Vec2& pos, Layer& layer) const;
	Vec2 getScreenDimensions() const;
	inline const std::string& str() const { return _content; }
};