#pragma once
#include "../sprite.h"
#include "../../math/math.h"
#include "../buffers/buffer.h"

struct Renderable
{
	const Buffer*		vbo;
	const IndexBuffer*	ibo;
	const Texture*		texture;
	Vec2				pos;
};