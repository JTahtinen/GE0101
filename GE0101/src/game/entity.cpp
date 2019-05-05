#include "entity.h"
#include <iostream>
#include <vector>
#include "../globals.h"
#include "../input/input.h"
#include "controller.h"
#include "camera.h"
#include "game.h"

static std::vector<GUID> availableGUIDs;

Entity::Entity(const Vec2& pos, Sprite* sprite)
	: _pos(pos)
	, _sprite(sprite)
	, _id(nextId())
	, _collider(&boxCollider)
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

	const auto& entities = game->getEntities();

	for (auto& other: entities)
	{
		if (other == this)
		{
			continue;
		}
		if (Collider::collidesWith(_pos, other->_pos, *_collider, *other->_collider))
		{
			MSG("Collision");
		}
	}

	_pos += _vel;
}

void Entity::render(Renderer* renderer, const Camera* camera) const
{
	if (renderer && _sprite)
	{
		renderer->submit(_sprite, _pos - camera->getPos());
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
