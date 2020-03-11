#include "polygon.h"
#include "../defs.h"
#include "../external/triangulate.h"

Polygon::Polygon(const std::vector<Vec2>& points)
    : _data({ points })
{
    if (points.size() < 3)
    {
        ERR("Could not create polygon. Amount of points was less than 3. Creating default polygon");
        _data.points.clear();
        _data.points.reserve(3);
        _data.points.emplace_back(0.0f, 0.0f);
        _data.points.emplace_back(0.1f, 0.1f);
        _data.points.emplace_back(0.2f, 0.0f);
    }
    triangulate();
}

void Polygon::triangulate()
{
    Triangulate::Process(_data.points, _data.indices);
}