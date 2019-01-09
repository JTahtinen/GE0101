#include "entity.h"
#include <iostream>
#include <vector>
#include "../globals.h"
#include "../input/input.h"

static std::vector<GUID> availableGUIDs;

Entity::Entity(const Vec2& pos, const Surface* sprite)
	: _pos(pos)
	, _sprite(sprite)
	, _id(nextId())
{
#ifdef _DEBUG
	std::cout << "Created Entity GUID: " << _id << std::endl;
#endif
}

Entity::Entity(const Surface* sprite)
	: Entity(Vec2(0, 0), sprite)
{
}

Entity::Entity()
	: Entity(nullptr)
{
}

Entity::~Entity()
{
	availableGUIDs.push_back(_id);
#ifdef _DEBUG
	std::cout << "Deleted Entity GUID: " << _id << std::endl;
#endif
}

void Entity::update(Game* game)
{
	_vel *= 0;
	Input& in = Input::instance();
	if (in.poll(KEY_LEFT))
	{
		_vel.add(-1.0f, 0);
	}
	if (in.poll(KEY_RIGHT))
	{
		_vel.add(1.0f, 0);
	}
	if (in.poll(KEY_UP))
	{
		_vel.add(0, -1.0f);
	}
	if (in.poll(KEY_DOWN))
	{
		_vel.add(0, 1.0f);
	}

	_pos += _vel;
	Renderable renderable(_sprite, _pos);
	renderer->submit(this);
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

