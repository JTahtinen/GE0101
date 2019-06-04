#include "camera.h"
#include "../graphics/window.h"
#include "game.h"

Camera::Camera(const Vec3& pos, float ratio)
	: _pos(pos)
	, _ratio(ratio)
{
}

Camera::Camera(float ratio)
	:
	Camera(Vec3(0, 0, 1), ratio)
{
}

void Camera::setPos(const Vec3& pos)
{
	_pos = pos;
}

void Camera::setPos(const Vec2& pos)
{
	setPos(Vec3(pos.x, pos.y, _pos.z));
}

void Camera::zoomIn()
{
	if (_zoomTarget > 0.2f)
	{
		_zoomTarget /= 2.0f;
	}
}

void Camera::zoomOut()
{
	if (_zoomTarget < 20.0f)
	{
		_zoomTarget *= 2.0f;
	}
}

void Camera::setZoom(float val)
{
	if (val > 0 && val < 7)
	{
		_pos.z = val;
		_zoomTarget = val;
	}
}

void Camera::update()
{
	if (_pos.z != _zoomTarget)
	{
		if (_zoomTarget > _pos.z)
		{
			float diff = _zoomTarget - _pos.z;
			_pos.z += diff / 0.1f * Game::frameTime;
			if (_pos.z > _zoomTarget || diff < 0.005f)
			{
				_pos.z = _zoomTarget;
			}
		}
		else
		{
			float diff = _pos.z - _zoomTarget;
			_pos.z -= diff / 0.1f * Game::frameTime;
			if (_pos.z < _zoomTarget || diff < 0.005f)
			{
				_pos.z = _zoomTarget;
			}
		}
	}
}