#include "polygonbatch.h"
#include "../polygon.h"

PolygonBatch::PolygonBatch()
{
	_data.reserve(50);
}

void PolygonBatch::submit(const Polygon& polygon, const Vec2& position)
{
	_data.emplace_back(PolygonRenderable { polygon, position });
}

void PolygonBatch::clear()
{
	_data.clear();
}