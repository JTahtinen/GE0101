#pragma once
#include "../../math/math.h"
#include "../font.h"
#include <string>
#include <vector>

struct LabelRenderable
{
	std::string content;
	Vec2 pos;
	float scale;
};

class TextBatch
{
	std::shared_ptr<const Font>					_refFont;
	std::vector<LabelRenderable>				_data;
public:
	TextBatch(std::shared_ptr<const Font> referenceFont);
	void submit(const std::string& content, const Vec2& pos, const float scale);
	inline bool checkCompatibility(const Font& font) const
	{
		return (font.getId() == _refFont->getId());
	}
	void bindFont() const;
	inline const std::vector<LabelRenderable>& getData() const { return _data; }
	inline const std::shared_ptr<const Font> getFont() const { return _refFont; }
	void clear();
};