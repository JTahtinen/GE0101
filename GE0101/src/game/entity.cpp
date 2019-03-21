#include "entity.h"
#include <iostream>
#include <vector>
#include "../globals.h"
#include "../input/input.h"
#include "controller.h"

static std::vector<GUID> availableGUIDs;

Entity::Entity(const Vec2& pos, Sprite* sprite)
	: _pos(pos)
	, _sprite(sprite)
	, _id(nextId())
{
#ifdef _DEBUG
	std::cout << "Created Entity GUID: " << _id << std::endl;
#endif
}

Entity::Entity(const Vec2& pos)
	: Entity(pos, nullptr)
{
}

Entity::Entity()
	: Entity(Vec2(0, 0))
{
}


Entity::~Entity()
{
	availableGUIDs.push_back(_id);
#ifdef _DEBUG
	std::cout << "Deleted Entity GUID: " << _id << std::endl;
#endif
}

void Entity::setVel(const Vec2& vel)
{
	_vel = vel;
}

void Entity::addVel(const Vec2& vel)
{
	_vel += vel;
}

void Entity::update(Game* game)
{
	_vel *= 0;
	if (_controller)
	{
		_controller->update(this);
	}

	_pos += _vel;
}

void Entity::render(Renderer* renderer)
{
	if (renderer && _sprite)
	{
		renderer->submit(_sprite, _pos);
	}
}

void Entity::addController(const Controller* controller)
{
	_controller = controller;
	if (!_controller)
	{
		gameLog.warning("Could not add controller - nullptr!");
	}
}

GUID Entity::nextId()
{
	static GUID numEntities = 0;
	if (!availableGUIDs.empty())
	{
		GUID guid = availableGUIDs.back();
		availableGUIDs.pop_back();
		return guid;
	}
	return numEntities++;
}
