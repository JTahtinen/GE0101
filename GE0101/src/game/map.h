#pragma once
#include "../graphics/sprite.h"
#include <vector>

#define TILE_SIZE 0.2f

class Game;
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
	static Map*				_instance;
public:
	~Map();
	void update(Game* game);
	void render(Renderer* renderer, const Camera* camera) const;
	static Map* createMap(int width, int height, const Game* game);
private:
	Map(int width, int height);
};