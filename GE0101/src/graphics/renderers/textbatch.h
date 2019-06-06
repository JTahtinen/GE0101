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
	std::vector<Label>				_data;
public:
	TextBatch(std::shared_ptr<const Font> reference);
	void submit(const std::string& content, const Vec2& pos, const float scale);
	inline bool checkCompatibility(const Font& font) const
	{
		return (font.getId() == _refFont->getId());
	}
	void bindFont() const;
	inline const std::vector<Label>& getData() const { return _data; }
	inline const std::shared_ptr<const Font> getFont() const { return _refFont; }
	void clear();
};