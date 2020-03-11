#pragma once
#include <vector>
#include "../math/vec2.h"

struct PolygonData
{
	std::vector<Vec2>			points;
	std::vector<unsigned int>	indices;
};

class Polygon
{
	PolygonData						_data;
public:
	Polygon(const std::vector<Vec2>& points);
	inline const PolygonData& getData() const { return _data; }
private:
	void triangulate();
};