#pragma once
#include "../graphics/screenelement.h"

class Frame : public ScreenElement
{
public:
	Frame(const Vec2& pos, const Vec2& dimensions);
	virtual void onHover(const Vec2& relativePos) override;
	virtual void onClick(const Vec2& relativePos) override;
	virtual void onClickHold(const Vec2& relativePos) override;
	virtual void onRelease(const Vec2& relativePos) override;
	virtual void onReleaseHover(const Vec2& relativePos) override;
	virtual void onExitHoverNoRelease(const Vec2& relativePos) override;
	virtual void onExit(const Vec2& relativePos) override;
	virtual void render(Layer& layer, const Vec2& pos) const override;
};