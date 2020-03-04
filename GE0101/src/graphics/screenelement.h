#pragma once
#include "../math/math.h"
#include <string>

class ScreenElement
{
protected:
	Vec2			_screenStart;
	Vec2			_screenEnd;
	Vec2			_screenDimensions;
public:
	ScreenElement(const Vec2& screenPos, const Vec2& screenDimensions) : _screenStart(screenPos), _screenEnd(screenPos + screenDimensions), _screenDimensions(screenDimensions) {}
	virtual void onHover(const Vec2& relativePos) {};
	virtual void onClick(const Vec2& relativePos) {};
	virtual void onClickHold(const Vec2& relativePos) {};
	virtual void onRelease(const Vec2& relativePos) {};
	virtual void onExit(const Vec2& relativePos) {}
	virtual const std::string getLabel() const { return ""; };
	inline void setScreenPos(const Vec2& screenPos) 
	{ 
		_screenStart = screenPos; 
		_screenEnd = screenPos + _screenDimensions;
	}
	inline void setScreenDimensions(const Vec2& dimensions)
	{
		_screenDimensions = dimensions;
		_screenEnd = _screenStart + dimensions;
	}
	inline const Vec2& getScreenPos() const { return _screenStart; }
	inline bool coversPoint(const Vec2& pos) const
	{
		return math::inBounds(pos.x, _screenStart.x, _screenEnd.x) && math::inBounds(pos.y, _screenStart.y, _screenEnd.y);
	}
};