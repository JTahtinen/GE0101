#pragma once
#include "../graphics/sprite.h"
#include <vector>
#include "../math/vec2.h"

#define TILE_SIZE 0.2f

class Application;
class Entity;
class Camera;
class Layer;
struct AssetData;

struct Tile
{
	std::string								name;
	std::shared_ptr<const Sprite>			sprite;
	bool									barrier;
};

class Map
{
	int											_width; 
	int											_height;
	std::vector<std::shared_ptr<Tile>>			_tiles;
public:
	~Map();
	void collisionCheck(Entity& entity) const;
	void render(Layer& layer, const Camera& camera) const;
	Vec2 getTilePos(const Vec2& absPos) const;
	inline std::shared_ptr<const Tile> getTile(int x, int y) const
	{
		if (x < 0 || x >= _width || y < 0 || y >= _height)
		{
			return nullptr;
		}
		return _tiles[x + y * _width];
	}
	static std::shared_ptr<Map> loadMap(const std::string& filepath, Application& app);
	Map() = default;
private:
	static std::shared_ptr<Tile> loadTile(const std::string& filepath, Application& app);
};