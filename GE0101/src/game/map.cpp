#include "map.h"
#include "game.h"
#include "../defs.h"
#include "../math/math.h"
#include "../graphics/layer.h"
#include "SDL2/SDL_image.h"
#include "states/gamestate.h"
#include "../physics/collider.h"
#include "entity/entity.h"
#include "../util/file.h"
#include "../application/assetmanager.h"
#include <sstream>

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
			std::shared_ptr<const Tile> currentTile = getTile(xTilePos, yTilePos);
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

std::shared_ptr<Map> Map::loadMap(const std::string& filepath, Game& game, AssetManager& assets)
{
	std::string mapFile = load_text_file(filepath);

	if (mapFile == "")
	{
		ERR("Could not load map: " << filepath);
		return nullptr;
	}

	std::stringstream ss(mapFile);
	std::string line = "";
	std::shared_ptr<Map> map = std::make_shared<Map>();
	std::unordered_map<int, std::shared_ptr<Tile>> tileTypeMap;
	while (ss >> line)
	{
		if (line == "numTileTypes:")
		{
			ss >> line;
			int numTileTypes = stoi(line);
			tileTypeMap.reserve(numTileTypes);
			continue;
		}
		if (line == "tile:")
		{
			ss >> line;
			std::string tileKey;
			ss >> tileKey;
			tileTypeMap.emplace(stoi(tileKey), loadTile(line, game, assets));
			continue;
		}
		if (line == "w:")
		{
			ss >> line;
			map->_width = stoi(line);
			continue;
		}
		if (line == "h:")
		{
			ss >> line;
			map->_height = stoi(line);
			continue;
		}
		if (line == "layout:")
		{
			map->_tiles.reserve(map->_width * map->_height);
			for (int y = 0; y < map->_height; ++y)
			{
				ss >> line;
				for (char tileSym : line)
				{
					int index = (int)(tileSym - '0');
					std::shared_ptr<Tile> tile = tileTypeMap[(int)(tileSym - '0')];
					if (tile)
					{
						map->_tiles.emplace_back(tile);
					}
				}
			}
		}
	}
	return map;
}

std::shared_ptr<Tile> Map::loadTile(const std::string& filepath, Game& game, AssetManager& assets)
{
	std::shared_ptr<Tile> tile = std::make_shared<Tile>();
	std::string file = load_text_file(filepath);
	std::istringstream ss(file);
	std::string line;
	while (ss >> line)
	{
		if (line == "name:")
		{
			ss >> line;
			tile->name = line;
		}
		if (line == "sprite:")
		{
			ss >> line;
			tile->sprite = assets.get<Sprite>(line);
		}
		if (line == "barrier:")
		{
			ss >> line;
			tile->barrier = (line == "true");
		}
	}
	return tile;
}