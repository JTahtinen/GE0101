#pragma once
#include "../math/vec2.h"
#include "../math/shapes.h"
struct Location
{
	Vec2		pos;
	Vec2		dimensions;
};

struct PhysicsObject
{
	Location	location;
	Vec2		force;
};