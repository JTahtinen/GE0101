#pragma once
#include "entity.h"

class Window;

class Camera
{
	Vec2			_pos;
	const float		_ratio;
	float			_zoom{ 1.0f };
	float			_zoomTarget{ 1.0f };
public:
	Camera(const Vec2& pos, float ratio);
	Camera(float ratio);
	void zoomIn();
	void zoomOut();
	void setZoom(float val);
	void setPos(const Vec2& pos);
	void update();
	inline float getWidthToHeightRatio() const
	{
		return _ratio;
	}
	inline float getHeightToWidthRatio() const
	{
		return 1.0f / _ratio;
	}
	inline float getLeft() const
	{
		return _pos.x - 1.0f / _zoom;
	}
	inline float getRight() const
	{
		return _pos.x + 1.0f / _zoom;
	}
	inline float getBottom() const
	{
		return _pos.y - getHeightToWidthRatio() / _zoom;
	}
	inline float getTop() const
	{
		return _pos.y + getHeightToWidthRatio() / _zoom;
	}
	inline const Vec2& getPos() const
	{
		return _pos;
	}
	inline float getZoom() const
	{
		return _zoom;
	}

};