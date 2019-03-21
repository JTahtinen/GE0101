#pragma once
#include "../sprite.h"
#include "../../math/math.h"
#include "../buffers/buffer.h"
#include "../buffers/indexbuffer.h"
#include "../shader.h"

struct Renderable
{
	const Sprite*	sprite;
	Vec2			pos;
};