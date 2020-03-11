#pragma once
#include <math.h>
#include "vec2.h"
#include "vec3.h"
#include "vec4.h"

namespace math
{
	struct Point
	{
		int x, y;
	};

	inline Point operator+(const Point& pointA, const Point& pointB)
	{
		return { pointA.x + pointB.x, pointA.y + pointB.y };
	}

	inline Point operator-(const Point& pointA, const Point& pointB)
	{
		return { pointA.x - pointB.x, pointA.y - pointB.y };
	}

	inline bool inBounds(float val, float floor, float ceil)
	{
		return (val >= floor && val < ceil);
	}

	inline bool inBounds(float xVal, float yVal, float xFloor, float yFloor, float xCeil, float yCeil)
	{
		return (inBounds(xVal, xFloor, xCeil) && inBounds(yVal, yFloor, yCeil));
	}

	inline Point roundVec2(const Vec2& vec)
	{
		return { (int)(vec.x + 0.5f), (int)(vec.y + 0.5f) };
	}

	inline int round(float val)
	{
		return (int)(val + 0.5f);
	}

	inline float projectToCoordinates(float sourceVal, float originMin, float originMax, float targetMin, float targetMax)
	{
		float originRange = originMax - originMin;
		float targetRange = targetMax - targetMin;
		return (sourceVal - originMin) / (originRange / targetRange) + targetMin;
	}

	inline float hypotenuse(const float a, const float b)
	{
		return sqrtf(a * a + b * b);
	}
}