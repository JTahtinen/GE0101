#pragma once
#include "../../math/vec2.h"
#include "../../math/vec4.h"
#include <vector>
#include "renderer.h"

struct QuadRenderable
{
	Vec2 pos;
	Vec2 dimensions;
	Vec4 color;
};

class QuadRenderer : public Renderer
{
	std::vector<QuadRenderable>		_renderables;
public:
	QuadRenderer();
	virtual ~QuadRenderer() override;
	void submit(const Vec2& pos, const Vec2& dimensions, const Vec4& color);
	virtual void flush() override;
};