#pragma once
#include "../../math/vec2.h"
#include "../../math/vec4.h"
#include "../shader.h"
#include <vector>

struct QuadRenderable
{
	Vec2 pos;
	Vec2 dimensions;
	Vec4 color;
};

class QuadRenderer
{
	Shader*							_shader;
	std::vector<QuadRenderable>		_renderables;
public:
	QuadRenderer();
	~QuadRenderer();
	void submit(const Vec2& pos, const Vec2& dimensions, const Vec4& color);
	void flush();
};