#pragma once
#include "../graphics/texture.h"
#include <vector>

#define TILE_SIZE 0.2f

class Game;
class Renderer;
struct Camera;

struct Tile
{
	const Texture*	texture;
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
	//void render(Renderer* renderer, float xOffset, float yOffset) const;
	void render(Renderer* renderer, const Camera* camera) const;
	static Map* createMap(int width, int height);
private:
	Map(int width, int height);
};