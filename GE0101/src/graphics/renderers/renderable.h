#pragma once
#include "../sprite.h"
#include "../../math/math.h"
#include "../buffers/buffer.h"
#include "../buffers/indexbuffer.h"
#include "../shader.h"

struct Renderable
{
	Buffer* data;
	IndexBuffer* indices;
	Sprite* sprite;
	Shader* shader;
	Vec2	pos;
};