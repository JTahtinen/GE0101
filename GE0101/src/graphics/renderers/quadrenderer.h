#pragma once
#include "renderer.h"
#include "../../math/math.h"
#include "quadbatch.h"
#include <vector>
#include "../buffers/indexbuffer.h"

class QuadRenderer : public Renderer
{
	QuadBatch			_batch;
	IndexBuffer			_ibo;
public:
	QuadRenderer(Window* win);
	void submit(const Vec2& pos, const Vec2& size, const Vec4& color);
	void flush() override;
	static void init(const Window& win);
	static void quit();
};