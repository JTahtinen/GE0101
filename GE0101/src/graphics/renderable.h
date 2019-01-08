#pragma once
#include "surface.h"
#include "../math/vec2.h"

struct Renderable
{
	const Vec2& pos;
	const Surface* sprite;
	Renderable(const Surface* sprite, const Vec2& pos) : pos(pos), sprite(sprite) {}
};