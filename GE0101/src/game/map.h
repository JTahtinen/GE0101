#pragma once
#include "../graphics/sprite.h"
#include <vector>
#include "../math/vec2.h"

#define TILE_SIZE 0.2f

class Game;
class Entity;
class Camera;
class Renderer;
struct AssetData;

struct Tile
{
	const Sprite*	sprite;
	bool			barrier;
};


class Map
{
	int						_width; 
	int						_height;
	std::vector<Tile*>		_tiles;
public:
	~Map();
	void collisionCheck(Entity* entity) const;
	void render(Renderer* renderer, const Camera* camera) const;
	Vec2 getTilePos(const Vec2& absPos) const;
	static Map* createMap(int width, int height, const Game* game);
	static Map* loadMap(const std::string& filepath, const Game* game);
	static bool init(const Game* game);
	static void quit();
	inline const Tile* getTile(int x, int y) const
	{
		if (x < 0 || x >= _width || y < 0 || y >= _height)
		{
			return nullptr;
		}
		return _tiles[x + y * _width];
	}
private:
	Map(int width, int height);
};