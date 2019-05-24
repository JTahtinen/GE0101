#include "gamedata.h"
#include "../defs.h"

template <typename T>
void push(T* unit, std::vector<T*>& data)
{
	if (!unit)
	{
		WARN("Could not push item to Game Data - nullptr exception");
		return;
	}

	for (auto& e : data)
	{
		if (e == unit)
		{
			WARN("Unit addition to Game Data ignored - unit already present");
		}
	}
	data.push_back(unit);
}

template <typename T>
T* find(const std::string& name, std::vector<T*>& data)
{
	for (auto& unit : data)
	{
		if (unit->getName() == name)
		{
			return unit;
		}
	}
	return nullptr;
}

template <typename T>
void pop(const std::string& name, std::vector<T*>& data)
{
	for (unsigned int i = 0; i < data.size(); ++i)
	{
		if (data[i]->getName() == name)
		{
			delete data[i];
			data[i] = nullptr;
			return;
		}
	}
}

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

void GameData::popEntity(const std::string& name)
{
	pop(name, _entities);
}

void GameData::loadSprite(const std::string& filepath)
{
	//TODO: sprite loading
}

void GameData::pushSprite(Sprite* unit)
{
	push(unit, _sprites);
}

Sprite* GameData::getSprite(const std::string& name)
{
	return find(name, _sprites);
}