#pragma once
#include "screenelement.h"
#include "../math/vec4.h"
#include "label.h"
#include "layer.h"
#include <string>

class Button : public ScreenElement
{
	void					(*_callback)();
	Vec4					_idleColor;
	Vec4					_pressedColor;
	Vec4					_hoverColor;
	Vec4*					_currentColor;
	Label					_label;
public:
	Button(const std::string& label, const Vec2& pos, const Vec2& dimensions, void (*callback)());
	virtual void onHover(const Vec2& relativePos) override;
	virtual void onClick(const Vec2& relativePos) override;
	virtual void onClickHold(const Vec2& relativePos) override;
	virtual void onRelease(const Vec2& relativePos) override;
	virtual void onReleaseHover(const Vec2& relativePos) override;
	virtual void onExitHoverNoRelease(const Vec2& relativePos) override;
	virtual void onExit(const Vec2& relativePos) override;
	virtual void render(Layer& layer) const override;
};