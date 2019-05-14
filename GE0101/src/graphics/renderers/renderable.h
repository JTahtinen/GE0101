#pragma once
#include "../sprite.h"
#include "../../math/math.h"
#include "../buffers/vertexarray.h"

struct Renderable
{
	const VertexArray*	vao;
	const IndexBuffer*	ibo;
	const Texture*		texture;
	Vec2				pos;
};