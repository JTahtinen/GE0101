#include "tile.h"


Tile::Tile(Sprite* sprite, bool barrier)
	:
	_sprite(sprite)
	, _barrier(barrier)
{
	//_renderable.data = 
}

Tile::Tile(Sprite* sprite)
	:
	Tile(sprite, false)
{
}

void Tile::render(Renderer* renderer)
{
	if (renderer && _sprite)
	{
		
	}
}