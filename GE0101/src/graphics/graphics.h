#pragma once
#include "surface.h"
#include "../math/vec2.h"

class Graphics
{
	Surface*		_target;
public:
	void setTarget(Surface* target);
	void drawPoint(float x, float y, unsigned int color);
	void drawPointAbs(int x, int y, unsigned int color);
	void drawRect(float xStart, float yStart, float xEnd, float yEnd, unsigned int color);
	void drawRectAbs(int xStart, int yStart, int xEnd, int yEnd, unsigned int color);
	void drawRectBordered(float xStart, float yStart, float xEnd, float yEnd, unsigned int color);
	void drawRectAbsBordered(int xStart, int yStart, int xEnd, int yEnd, unsigned int color);
private:
	Vec2 translatePoint(float x, float y);
	inline void drawPointFast(int x, int y, unsigned int color)
	{
		_target->_pixels[x + y * _target->getWidth()] = color;
	}
	inline void drawRectFast(int xStart, int yStart, int xEnd, int yEnd, unsigned int color)
	{
		for (int y = yStart; y < yEnd; ++y)
		{
			for (int x = xStart; x < xEnd; ++x)
			{
				_target->_pixels[x + y * _target->getWidth()] = color;
			}
		}
	}

};