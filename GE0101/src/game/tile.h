#pragma once
#include "../graphics/sprite.h"
#include "../graphics/renderers/renderer.h"

class Tile
{
	Sprite*		_sprite;
	bool		_barrier;
	Renderable	_renderable;
public:
	Tile(Sprite* sprite, bool barrier);
	Tile(Sprite* sprite);
	void render(Renderer* renderer);
};