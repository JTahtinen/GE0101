#pragma once
#include "entity.h"

struct Camera
{
	Vec2			pos;
	float			xRatio;
	float			yRatio;
	float			zoom{ 1 };
};