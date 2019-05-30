#pragma once
#include "entity.h"

class Window;

class Camera
{
	Vec4			_pos;
	const float		_ratio;
	//float			_zoom{ 1.0f };
	float			_zoomTarget{ 1.0f };
public:
	Camera(const Vec4& pos, float ratio);
	Camera(float ratio);
	void zoomIn();
	void zoomOut();
	void setZoom(float val);
	void setPos(const Vec4& pos);
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
		return _pos.x - _pos.z;
	}
	inline float getRight() const
	{
		return _pos.x + _pos.z;
	}
	inline float getBottom() const
	{
		return _pos.y - getHeightToWidthRatio() * _pos.z;
	}
	inline float getTop() const
	{
		return _pos.y + getHeightToWidthRatio() * _pos.z;
	}
	inline const Vec4& getPos() const
	{
		return _pos;
	}


};