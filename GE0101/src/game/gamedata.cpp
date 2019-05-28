#include "gamedata.h"
#include "../defs.h"
#include "assets/dataops.h"


GameData::GameData()
{
	_entities.reserve(200);
	_sprites.reserve(30);
}

GameData::~GameData()
{
	for (auto& entity : _entities)
	{
		delete entity;
	}
	for (auto& sprite : _sprites)
	{
		delete sprite;
	}
}

void GameData::loadEntity(const std::string& filepath)
{
	//TODO: Entity file loading
}

void GameData::pushEntity(Entity* unit)
{
	push(unit, _entities);
}

Entity* GameData::getEntity(const std::string& name)
{
	return find(name, _entities);
}

void GameData::removeEntity(const std::string& name)
{
	removeUnit(name, _entities);
}