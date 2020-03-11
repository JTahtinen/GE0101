#pragma once
#include "../../math/math.h"
#include <vector>

class Polygon;

struct PolygonRenderable
{
	const Polygon&							polygon;
	const Vec2								position;
};

class PolygonBatch
{
	std::vector<PolygonRenderable>			_data;
public:
	PolygonBatch();
	void submit(const Polygon& polygon, const Vec2& position);
	inline const std::vector<PolygonRenderable>& getData() const { return _data; }
	void clear();
};