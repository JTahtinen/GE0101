#include "map.h"
#include "game.h"
#include "../graphics/graphics.h"

Map::Map(int width, int height)
	: _width(width)
	, _height(height)
{
}

void Map::update(Game* game)
{

}

void Map::render(Graphics* g)
{
	for (int y = 0; y < _height; ++y)
	{
		for (int x = 0; x < _width; ++x)
		{
			float xStart = x * 32;
			float yStart = y * 32;
			float xEnd = xStart + 32;
			float yEnd = yStart + 32;
			g->drawRectAbsBordered(xStart, yStart, xEnd, yEnd, 0x0000ff);

		}
	}
}