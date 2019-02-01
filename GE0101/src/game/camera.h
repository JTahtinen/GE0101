#pragma once
#include "entity.h"

struct Camera
{
	Vec2			pos;
	float			ratio;
	float			zoom{ 1 };
};