#include "map.h"
#include "game.h"
#include "../graphics/buffers/buffer.h"
#include "../graphics/buffers/indexbuffer.h"
#include "../defs.h"
#include "../math/vec2.h"


Map* Map::_instance;

Map::Map(int width, int height)
	: _width(width)
	, _height(height)
{
	ASSERT(width * height > 0)

	
	_tiles.reserve(width * height);
	for (int i = 0; i < width * height; ++i)
	{
		_tiles.push_back(&defTile);
	}
}

Map::~Map()
{
	delete tileVertices;
	delete tileIndices;
}

void Map::update(Game* game)
{

}

void Map::render(Renderer* renderer, float xOffset, float yOffset) const
{
	if (renderer)
	{
		for (int y = 0; y < _height; ++y)
		{
			for (int x = 0; x < _width; ++x)
			{
				renderer->submit(tileVertices, tileIndices, _tiles[x + y * _width]->texture, Vec2(x * 0.2f + xOffset, y * 0.2f + yOffset));
			}
		}
	}
}

Map* Map::createMap(int width, int height)
{
	if (Map::_instance)
	{
		delete Map::_instance;
	}

	Map::_instance = new Map(width, height);

	return Map::_instance;
}