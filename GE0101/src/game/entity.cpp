#include "entity.h"
#include <iostream>
#include <vector>
#include "../globals.h"
#include "../input/input.h"
#include "camera.h"
#include "game.h"
#include "../physics/collider.h"

static std::vector<GUID> availableGUIDs;

Entity::Entity(const Vec2& pos, Sprite* sprite)
	:
	_sprite(sprite)
	, _id(nextId())
	, _object({{ pos, Vec2(0.2f, 0.2f) }, Vec2(0, 0)})
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

void Entity::setForce(const Vec2& force)
{
	_object.force = force * Game::frameTime;
}

void Entity::addForce(const Vec2& force)
{
	_object.force += force * Game::frameTime;
}

void Entity::update(Game* game)
{
	Collider::instance().push(&_object);
}

void Entity::render(Renderer* renderer, const Camera* camera) const
{
	if (renderer && _sprite)
	{
		Renderable2D* renderable = Renderable2D::createRenderable2D(_sprite, _object.location.pos - camera->getPos());
		renderer->submit(renderable);
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
