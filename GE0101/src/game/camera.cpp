#include "camera.h"
#include "../graphics/window.h"
#include "game.h"

Camera::Camera(const Vec2& pos, float ratio)
	:
	_pos(pos)
	, _ratio(ratio)
{
}

Camera::Camera(float ratio)
	:
	Camera(Vec2(0, 0), ratio)
{
}

void Camera::setPos(const Vec2& pos)
{
	_pos = pos;
}

void Camera::zoomIn()
{
	if (_zoomTarget < 20)
	{
		_zoomTarget *= 2.0f;
	}
}

void Camera::zoomOut()
{
	if (_zoomTarget > 0.2)
	{
		_zoomTarget /= 2.0f;
	}
}

void Camera::setZoom(float val)
{
	if (val > 0 && val < 7)
	{
		_zoom = val;
		_zoomTarget = val;
	}
}

void Camera::update()
{
	if (_zoom != _zoomTarget)
	{
		if (_zoomTarget > _zoom)
		{
			float diff = _zoomTarget - _zoom;
			_zoom += diff / 0.1f * Game::frameTime;
			if (_zoom > _zoomTarget || diff < 0.005f)
			{
				_zoom = _zoomTarget;
			}
		}
		else
		{
			float diff = _zoom- _zoomTarget;
			_zoom -= diff / 0.1f * Game::frameTime;
			if (_zoom < _zoomTarget || diff < 0.005f)
			{
				_zoom = _zoomTarget;
			}
		}
	}
}