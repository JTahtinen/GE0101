#pragma once
#include "entity/entity.h"
#include "../math/vec3.h"
#include <memory>

class Window;

class Camera
{
	Vec3			_pos;
	const float		_ratio;
	//float			_zoom{ 1.0f };
	float			_zoomTarget{ 1.0f };
public:
	Camera(const Vec3& pos, float ratio);
	Camera(float ratio);
	void zoomIn();
	void zoomOut();
	void setZoom(float val);
	void setPos(const Vec3& pos);
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
		return _pos.x - 1.0f * _pos.z;
	}
	inline float getRight() const
	{
		return _pos.x + 1.0f * _pos.z;
	}
	inline float getBottom() const
	{
		return _pos.y - getHeightToWidthRatio() * _pos.z;
	}
	inline float getTop() const
	{
		return _pos.y + getHeightToWidthRatio() * _pos.z;
	}
	inline Vec2 getArea() const
	{
		return Vec2(getRight() - getLeft(), getTop() - getBottom());
	}
	inline Vec2 getWorldPoint(const Vec2& screenPoint) const
	{
		Vec2 area = getArea();
		return Vec2(getLeft() + screenPoint.x * area.x, getBottom() + screenPoint.y * area.y);
	}
	inline bool inBounds(const Vec2& pos, const Vec2& size) const 
	{
		return (pos.x + size.x > getLeft() && pos.x < getRight()
			&& pos.y + size.y > getBottom() && pos.y < getTop());
	}
	inline const Vec3& getPos() const
	{
		return _pos;
	}


};