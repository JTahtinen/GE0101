#include "textbatch.h"
#include "../../defs.h"

TextBatch::TextBatch(std::shared_ptr<const Font> referenceFont, float referenceScale)
	: _refFont(referenceFont)
	, _refScale(referenceScale)
{
	_data.reserve(30);
}

void TextBatch::submit(const std::string& content, const Vec2& pos, const float scale)
{
	if (content != "")
	{
		_data.emplace_back(Label{ content, pos, scale });
	}
}

void TextBatch::bindFont() const
{
	_refFont->bind();
}

void TextBatch::clear()
{
	_data.clear();
}