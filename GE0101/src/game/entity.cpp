#include "entity.h"
#include <iostream>
#include <vector>
#include "../globals.h"
#include "../input/input.h"
#include "controller.h"

static std::vector<GUID> availableGUIDs;

Entity::Entity(const Vec2& pos)
	: _pos(pos)
	, _id(nextId())
{
#ifdef _DEBUG
	std::cout << "Created Entity GUID: " << _id << std::endl;
#endif
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

void Entity::addController(const Controller* controller)
{
	_controller = controller;
	if (!_controller)
	{
		gameLog.warning("Could not add controller - nullptr!");
	}
}
