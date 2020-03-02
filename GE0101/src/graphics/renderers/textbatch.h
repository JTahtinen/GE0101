#pragma once
#include "../../math/math.h"
#include "../font.h"
#include <string>
#include <vector>

struct Label
{
	std::string content;
	Vec2 pos;
	float scale;
};

class TextBatch
{
	std::shared_ptr<const Font>		_refFont;
	float							_refScale;
	std::vector<Label>				_data;
public:
	TextBatch(std::shared_ptr<const Font> referenceFont, float referenceScale);
	void submit(const std::string& content, const Vec2& pos, const float scale);
	inline bool checkCompatibility(const Font& font, float scale) const
	{
		return (font.getId() == _refFont->getId() && scale == _refScale);
	}
	void bindFont() const;
	inline const std::vector<Label>& getData() const { return _data; }
	inline const std::shared_ptr<const Font> getFont() const { return _refFont; }
	inline float getScale() const { return _refScale; }
	void clear();
};