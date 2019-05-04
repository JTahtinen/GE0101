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

	float screenTileSize = TILE_SIZE * camera->zoom;
	Vec2 scrCamPos = camera->pos * camera->zoom;

	static float halfTileSize = screenTileSize / 2.0f;


	int xStartTile;
	int yStartTile;

	int xEndTile;
	int yEndTile;

	float left		= scrCamPos.x - 1.0f / camera->zoom;
	float right		= scrCamPos.x + 1.0f / camera->zoom;
	float bottom	= scrCamPos.y - camera->yRatio / camera->zoom;
	float top		= scrCamPos.y + camera->yRatio / camera->zoom;

	xStartTile		= (int)((left	+ halfTileSize) / screenTileSize);
	xEndTile		= (int)((right	+ halfTileSize) / screenTileSize) + 1;
	yStartTile		= (int)((bottom	+ halfTileSize) / screenTileSize);
	yEndTile		= (int)((top	+ halfTileSize) / screenTileSize) + 1;



	if (xStartTile < 0) xStartTile = 0;
	if (xStartTile > _width) xStartTile = _width;

	if (xEndTile < 0) xEndTile = 0;
	if (xEndTile > _width) xEndTile = _width;

	if (yStartTile < 0) yStartTile = 0;
	if (yStartTile > _height) yStartTile = _height;

	if (yEndTile < 0) yEndTile = 0;
	if (yEndTile > _height) yEndTile = _height;

	MSG("XStart: " << xStartTile);
	MSG("XEnd:   " << xEndTile << std::endl);
	MSG("YStart: " << yStartTile);
	MSG("YEnd:   " << yEndTile << std::endl);

	
	for (int y = yStartTile; y < yEndTile; ++y)
	{
		for (int x = xStartTile; x < xEndTile; ++x)
		{
			renderer->submit(tileVertices, tileIndices, _tiles[x + y * _width]->texture, Vec2(-camPos.x + x * TILE_SIZE, -camPos.y + y * TILE_SIZE));
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