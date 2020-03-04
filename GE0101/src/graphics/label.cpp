#include "label.h"
#include "../globals.h"
#include "../defs.h"

Label::Label(const std::string& content, const float scale, std::shared_ptr<const Font> font)
	: _content(content)
	, _scale(scale)
	, _font(font)
	, _screenWidth(0)
	, _screenHeight(0)
{
	ASSERT(_font);
	for (const char l : _content)
	{
		const Letter* letter = _font->getLetter(l);
		_screenWidth += letter->width;
		float curLetterHeight = letter->height;
		if (curLetterHeight > _screenHeight)
		{
			_screenHeight = curLetterHeight;
		}
	}

	_screenWidth *= _scale;
	_screenHeight *= _scale;
}

Label::Label(const std::string& content, const float scale)
	: Label(content, scale, g_assetManager.get<Font>("res/fonts/liberation_serif"))
{
}

void Label::render(const Vec2& pos, Layer& layer) const
{
	if (_content != "")
	{
		layer.submitText(_content, pos, _scale);
	}
}

Vec2 Label::getScreenDimensions() const
{
	return Vec2(_screenWidth, _screenHeight);
}