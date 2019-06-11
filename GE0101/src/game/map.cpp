#include "map.h"
#include "game.h"
#include "../graphics/buffers/buffer.h"
#include "../graphics/buffers/indexbuffer.h"
#include "../defs.h"
#include "../math/vec2.h"
#include "../math/math.h"
#include "../graphics/layer.h"
#include "SDL2/SDL_image.h"
#include "states/gamestate.h"
#include "../physics/collider.h"
#include "entity/entity.h"

static bool isInit = false;

static Tile* floorTile;
static Tile* wallTile;



Map::Map(int width, int height)
	: _width(width)
	, _height(height)
{
	ASSERT(width * height > 0);
	
	
	_tiles.reserve(width * height);
	for (int i = 0; i < width * height; ++i)
	{
		_tiles.push_back(floorTile);
	}
}

Map::~Map()
{
}

void Map::collisionCheck(Entity& entity) const
{
	static Vec2 tileDim(TILE_SIZE, TILE_SIZE);
	Vec2 entityTile = getTilePos(entity.getPhysics()->getPos().center);
	for (int row = 0; row < 3; ++row)
	{
		for (int column = 0; column < 3; ++column)
		{
			int xTilePos = (int)(entityTile.x - 1 + column);
			int yTilePos = (int)(entityTile.y - 1 + row);
			const Tile* currentTile = getTile(xTilePos, yTilePos);
			if (currentTile && currentTile->barrier)
			{
				PhysicsObject tileObj(Vec2((float)(xTilePos * TILE_SIZE), (float)(yTilePos * TILE_SIZE)), Vec2(TILE_SIZE, TILE_SIZE));
				entity._object.collisionCheck(tileObj);
			}
		}
	}
}

void Map::render(Layer& layer, const Camera& camera) const
{
	int xStartTile		= (int)((camera.getLeft()) / TILE_SIZE);
	int xEndTile		= (int)((camera.getRight() + TILE_SIZE) / TILE_SIZE);
	int yStartTile		= (int)((camera.getBottom() + TILE_SIZE) / TILE_SIZE);
	int yEndTile		= (int)((camera.getTop() + 2 * TILE_SIZE) / TILE_SIZE);

	if (xStartTile < 0) xStartTile = 0;
	if (xStartTile > _width) return;

	if (xEndTile < 0) return;
	if (xEndTile > _width) xEndTile = _width;

	if (yStartTile < 0) yStartTile = 0;
	if (yStartTile > _height) return;

	if (yEndTile < 0) return;
	if (yEndTile > _height) yEndTile = _height;

	const Vec3& camPos = camera.getPos();
	//const float zoom = camera->getZoom();
	//MSG(yEndTile);
	for (int y = yStartTile; y < yEndTile; ++y)
	{
		for (int x = xStartTile; x < xEndTile; ++x)
		{
			std::shared_ptr<const Sprite> tile = _tiles[x + y * _width]->sprite;

			layer.submitSprite(tile, Vec2(x * TILE_SIZE, y * TILE_SIZE), -camPos);
		}
	}
}

Vec2 Map::getTilePos(const Vec2& absPos) const
{
	return Vec2(absPos.x / TILE_SIZE, absPos.y / TILE_SIZE);
}

Map* Map::createMap(int width, int height, const Game& game)
{
	if (!isInit)
	{
		init(game);
		if (!isInit)
		{
			ERR("Could not create map - game was nullptr");
			return nullptr;
		}
	}
	Map* map = new Map(width, height);

	return map;
}

Map* Map::loadMap(const std::string& filepath, const Game& game)
{
	if (!isInit)
	{
		isInit = init(game);
		if (!isInit)
		{
			return nullptr;
		}
	}
	SDL_Surface* mapImage = IMG_Load(filepath.c_str());
	if (!mapImage)
	{
		ERR("Could not load map file: " << filepath);
		return nullptr;
	}

	
	int width = mapImage->w;
	int height = mapImage->h;
	Map* map = new Map(width, height);
	unsigned int* tilePix = (unsigned int*)mapImage->pixels;
	Tile* currentTile;
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			switch (tilePix[x + (height - 1 - y) * width])
			{
			case 0xffff0000:
				currentTile = floorTile;
				break;
			case 0xff0000ff:
				currentTile = wallTile;
				break;
			default:
				currentTile = wallTile;
				break;
			}
			map->_tiles[x + y * width] = currentTile;

		}
	}
	return map;
}

bool Map::init(const Game& game)
{
	floorTile = new Tile();
	floorTile->barrier = false;
	floorTile->sprite = game.getAssetData()->spriteData.getSprite("floor");

	wallTile = new Tile();
	wallTile->barrier = true;
	wallTile->sprite = game.getAssetData()->spriteData.getSprite("wall");
	return true;
}

void Map::quit()
{
	delete floorTile;
	floorTile = nullptr;
	delete wallTile;
	wallTile = nullptr;
}