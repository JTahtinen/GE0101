#include "quadbatch.h"

QuadBatch::QuadBatch()
{
	_data.reserve(50);
}

void QuadBatch::submit(const Vec2& pos, const Vec2& size, const Vec4& color)
{
	_data.emplace_back(QuadRenderable{ pos, size, color });
}

void QuadBatch::clear()
{
	_data.clear();
}