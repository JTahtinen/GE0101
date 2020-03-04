#include "button.h"

#define BUTTON_TEXT_MARGIN 0.02f

Button::Button(const std::string& label, const Vec2& pos, const Vec2& dimensions, void (*callback)())
	: ScreenElement(pos, dimensions)
	, _idleColor(0.4f, 0.4f, 0.4f, 1.0f)
	, _pressedColor(0.8f, 0.8f, 0.8f, 1.0f)
	, _hoverColor(0.6f, 0.6f, 0.6f, 1.0f)
	, _label(label, 0.6f)
	, _currentColor(&_idleColor)
	, _callback(callback)
{
	_label.setScaleToFit(Vec2(_screenDimensions.x - BUTTON_TEXT_MARGIN, _screenDimensions.y - BUTTON_TEXT_MARGIN));
}

void Button::onHover(const Vec2& relativePos)
{
	_currentColor = &_hoverColor;
}

void Button::onClick(const Vec2& relativePos)
{

}

void Button::onClickHold(const Vec2& relativePos)
{
	_currentColor = &_pressedColor;
}

void Button::onRelease(const Vec2& relativePos)
{
	_currentColor = &_idleColor;
}

void Button::onReleaseHover(const Vec2& relativePos)
{
	_callback();
}

void Button::onExitHoverNoRelease(const Vec2& relativePos)
{
	_currentColor = &_idleColor;
}

void Button::onExit(const Vec2& relativePos)
{
	_currentColor = &_idleColor;
}

void Button::render(Layer& layer) const
{
	layer.submitQuad(_screenStart, _screenDimensions, *_currentColor);
	const Vec2& labelDim = _label.getScreenDimensions();
	Vec2 labelPos(_screenStart.x + _screenDimensions.x * 0.5f - labelDim.x * 0.5f,
						_screenStart.y + _screenDimensions.y * 0.5f - labelDim.y * 0.5f);
	_label.render(labelPos, layer);	
}