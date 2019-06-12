#pragma once
#include "entity/entity.h"
#include "../math/vec3.h"

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
	inline bool inBounds(const Vec2& pos, const Vec2& size) const 
	{
		return (pos.x + size.x > getLeft() && pos.x < getRight()
			&& pos.y > getBottom() && pos.y - size.y < getTop());
	}
	inline const Vec3& getPos() const
	{
		return _pos;
	}


};