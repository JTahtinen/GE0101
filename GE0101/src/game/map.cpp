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

void Map::render(Renderer* renderer, const Camera* camera) const
{
	const Vec2& camPos = camera->pos;

	int xStartTile;
	int yStartTile;

	int xEndTile;
	int yEndTile;

	float left = camPos.x - 1.0f;
	float right = camPos.x + 1.0f;
	float top = camPos.y + 1.0f;
	float bottom = camPos.y - camera->yRatio;

	if (left < 0.0f) left = 0.0f;
	if (right < 0.0f) right = 0.0f;
	if (top < 0.0f) top = 0.0f;
	if (bottom < 0.0f) bottom = 0.0f;

	xStartTile = (int)(left / TILE_SIZE);
	xEndTile = (int)(right / TILE_SIZE);
	yStartTile = (int)(bottom / TILE_SIZE);
	yEndTile = (int)(top / TILE_SIZE);



	if (xStartTile < 0) xStartTile = 0;
	if (xStartTile > _width) xStartTile = _width;

	if (xEndTile < 0) xEndTile = 0;
	if (xEndTile > _width) xEndTile = _width;

	if (yStartTile < 0) yStartTile = 0;
	if (yStartTile > _height) yStartTile = _height;

	if (yEndTile < 0) yEndTile = 0;
	if (yEndTile > _height) yEndTile = _height;

	MSG("YStart: " << yStartTile);
	MSG("YEnd:" << yEndTile);

	for (int y = yStartTile; y < yEndTile; ++y)
	{
		for (int x = xStartTile; x < xEndTile; ++x)
		{
			renderer->submit(tileVertices, tileIndices, _tiles[x + y * _width]->texture, Vec2(-camPos.x + x * TILE_SIZE + TILE_SIZE / 2.0f, -camPos.y + y * TILE_SIZE + TILE_SIZE / 2.0f));
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