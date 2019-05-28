#pragma once
#include <vector>
#include "../graphics/sprite.h"
#include "entity.h"
#include "assets/dataops.h"

class GameData
{
	std::vector<Entity*>		_entities;
	std::vector<Sprite*>		_sprites;
public:
	GameData();
	~GameData();
	DATA_OPERATIONS(Entity);
};