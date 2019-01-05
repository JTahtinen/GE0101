#include "graphics.h"
#include "../math/vec2.h"
#include "../math/math.h"
#include <iostream>

Vec2 Graphics::translatePoint(float x, float y)
{
	int halfW = _target->getWidth() / 2;
	int halfH = _target->getHeight() / 2;
	
	return Vec2(
		x * halfW + halfW,
		y * halfH + halfH);
}

void Graphics::setTarget(Surface* target)
{
	if (target)
	{
		_target = target;
	}
	else
	{
		std::cout << "Warning: Could not set graphics target: surface was null!" << std::endl;
	}
}

void Graphics::drawPoint(float x, float y, unsigned int color)
{
	Vec2 point = translatePoint(x, y);
	int targetW = _target->getWidth();
	int targetH = _target->getHeight();
	if (point.x >= 0 && point.x < targetW && point.y >= 0 && point.y < targetH)
	{
		drawPointFast((int)point.x, (int)point.y, color);
	}
}

void Graphics::drawPointAbs(int x, int y, unsigned int color)
{
	if (math::inBounds(x, y, 0, 0, _target->getWidth(), _target->getHeight()))
	{
		drawPointFast(x, y, color);
	}
}

void Graphics::drawRect(float xStart, float yStart, float xEnd, float yEnd, unsigned int color)
{
	Vec2 start = translatePoint(xStart, yStart);
	Vec2 end = translatePoint(xEnd, yEnd);

	int targetW = _target->getWidth();
	int targetH = _target->getHeight();

	if (start.x >= targetW || start.y >= targetH || end.x < 1 || end.y < 1)
	{
		return;
	}

	if (start.x < 0) start.x = 0;
	if (start.y < 0) start.y = 0;
	if (end.x > targetW) end.x = (float)targetW;
	if (end.y > targetH) end.y = (float)targetH;

	for (int y = (int)start.y; y < (int)end.y; ++y)
	{
		for (int x = (int)start.x; x < (int)end.x; ++x)
		{
			drawPointFast(x, y, color);
		}
	}
}

void Graphics::drawRectAbs(int xStart, int yStart, int xEnd, int yEnd, unsigned int color)
{
	int targetW = _target->getWidth();
	int targetH = _target->getHeight();

	if (xStart >= targetW || yStart >= targetH || xEnd < 1 || yEnd < 1)
	{
		return;
	}

	int finalXStart;
	int finalYStart;
	int finalXEnd;
	int finalYEnd;

	if (xStart < 0) { finalXStart = 0; }
	else finalXStart = xStart;
	if (yStart < 0) { finalYStart = 0; }
	else finalYStart = yStart;
	if (xEnd > targetW) {finalXEnd = (float)targetW;}
	else finalXEnd = xEnd;
	if (yEnd > targetH) {finalYEnd = (float)targetH;}
	else finalYEnd = yEnd;

	for (int y = finalYStart; y < finalYEnd; ++y)
	{
		for (int x = finalXStart; x < finalXEnd; ++x)
		{
			drawPointAbs(x, y, color);
		}
	}
}

void Graphics::drawRectBordered(float xStart, float yStart, float xEnd, float yEnd, unsigned int color)
{
	drawRect(xStart, yStart, xEnd, yEnd, 0);
	drawRect(xStart + 0.001f, yStart + 0.001f, xEnd - 0.001f, yEnd - 0.001f, color);
}

void Graphics::drawRectAbsBordered(int xStart, int yStart, int xEnd, int yEnd, unsigned int color)
{
	drawRectAbs(xStart, yStart, xEnd, yEnd, 0);
	drawRectAbs(xStart + 1, yStart + 1, xEnd - 1, yEnd - 1, color);
}
