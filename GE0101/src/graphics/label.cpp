#include "label.h"
#include "../globals.h"
#include "../defs.h"

Label::Label(const std::string& content, const float scale, std::shared_ptr<const Font> font)
	: _content(content)
	, _scale(scale)
	, _font(font)
	, _screenDimensions(0, 0)
{
	ASSERT(_font);
	calculateDimensions();
}

Label::Label(const std::string& content, const float scale)
	: Label(content, scale, g_assetManager.get<Font>("res/fonts/liberation_serif"))
{
}

void Label::setScale(const float scale)
{
	_scale = scale;
	calculateDimensions();
}

void Label::render(const Vec2& pos, Layer& layer) const
{
	if (_content != "")
	{
		layer.submitText(_content, pos, _scale);
	}
}

const Vec2& Label::getScreenDimensions() const
{
	return _screenDimensions;
}

void Label::setScaleToFit(const Vec2& dimensions)
{
	setScale(1.0f);
	setScale(dimensions.x / _screenDimensions.x);

	if (_screenDimensions.y > dimensions.y)
	{
		setScale(dimensions.y / _screenDimensions.y);
	}
}

void Label::calculateDimensions()
{
	_screenDimensions = Vec2(0, 0);
	for (const char l : _content)
	{
		const Letter* letter = _font->getLetter(l);
		if (!letter)
		{
			continue;
		}
		_screenDimensions.x += letter->xAdvance;
		float curLetterHeight = letter->height;
		if (curLetterHeight > _screenDimensions.y)
		{
			_screenDimensions.y = curLetterHeight;
		}
	}
	_screenDimensions *= _scale;
}