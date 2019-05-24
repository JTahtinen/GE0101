#pragma once
#include <vector>
#include "../graphics/sprite.h"
#include "entity.h"

#define GAME_DATA_OPERATIONS(t) void load##t(const std::string& filepath);\
								void push##t(##t* unit);\
								##t* get##t(const std::string& name);\
								void pop##t(const std::string& name)

class GameData
{
	std::vector<Entity*>		_entities;
	std::vector<Sprite*>		_sprites;
public:
	GameData();
	~GameData();
	GAME_DATA_OPERATIONS(Entity);
	GAME_DATA_OPERATIONS(Sprite);
};