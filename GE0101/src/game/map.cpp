#include "map.h"
#include "game.h"
#include "../graphics/buffers/buffer.h"
#include "../graphics/buffers/indexbuffer.h"
#include "../defs.h"
#include "../math/vec2.h"
#include "../math/math.h"
#include "../graphics/renderers/renderer.h"


Map* Map::_instance;
static Tile* defTile;

Map::Map(int width, int height)
	: _width(width)
	, _height(height)
{
	ASSERT(width * height > 0);
	
	
	_tiles.reserve(width * height);
	for (int i = 0; i < width * height; ++i)
	{
		_tiles.push_back(defTile);
	}
}

Map::~Map()
{
	delete defTile;
}

void Map::update(Game* game)
{
}

void Map::render(Renderer* renderer, const Camera* camera) const
{
	float halfTileSize = TILE_SIZE / 2.0f;

	int xStartTile		= (int)((camera->getLeft()	 + halfTileSize) / TILE_SIZE);
	int xEndTile		= (int)((camera->getRight()  + halfTileSize) / TILE_SIZE) + 1;
	int yStartTile		= (int)((camera->getBottom() + halfTileSize) / TILE_SIZE);
	int yEndTile		= (int)((camera->getTop()	 + halfTileSize) / TILE_SIZE) + 1;


	if (xStartTile < 0) xStartTile = 0;
	if (xStartTile > _width) return;

	if (xEndTile < 0) return;
	if (xEndTile > _width) xEndTile = _width;

	if (yStartTile < 0) yStartTile = 0;
	if (yStartTile > _height) return;

	if (yEndTile < 0) return;
	if (yEndTile > _height) yEndTile = _height;

	const Vec2& camPos = camera->getPos();
	const float zoom = camera->getZoom();

	for (int y = yStartTile; y < yEndTile; ++y)
	{
		for (int x = xStartTile; x < xEndTile; ++x)
		{
			Renderable2D* tile = 
				Renderable2D::createRenderable2D(_tiles[x + y * _width]->sprite,
				Vec2(
					-camPos.x + x * TILE_SIZE,
					-camPos.y + y * TILE_SIZE), zoom);
			renderer->submit(tile);
		}
	}
}

Map* Map::createMap(int width, int height, GameData* gameData)
{
	if (Map::_instance)
	{
		delete Map::_instance;
	}		

	defTile = new Tile();
	defTile->barrier = false;
	defTile->sprite = gameData->getSprite("snowman");

	Map::_instance = new Map(width, height);

	return Map::_instance;
}