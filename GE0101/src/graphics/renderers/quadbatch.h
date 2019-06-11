#pragma once
#include "../../math/math.h"
#include <vector>

struct QuadRenderable
{
	Vec2 pos;
	Vec2 size;
	Vec4 color;
};

class QuadBatch
{
	std::vector<QuadRenderable>			_data;
public:
	QuadBatch();
	void submit(const Vec2& pos, const Vec2& size, const Vec4& color);
	inline const std::vector<QuadRenderable>& getData() const { return _data; }
	void clear();
};