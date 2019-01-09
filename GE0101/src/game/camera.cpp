#include "camera.h"


Camera::Camera(const Surface& target)
	: _targetW(target.getWidth())
	, _targetH(target.getHeight())
{
}

void Camera::update(Game* game)
{	
}

Vec2 Camera::getCameraCorrection(const Vec2& pos) const
{
	return Vec2(pos.x - _pos.x + _targetW / 2, pos.y - _pos.y + _targetH / 2);
}