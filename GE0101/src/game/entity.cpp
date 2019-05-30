#include "entity.h"
#include <iostream>
#include <vector>
#include "../globals.h"
#include "../input/input.h"
#include "camera.h"
#include "game.h"
#include "../physics/collider.h"
#include "../defs.h"
#include "gamestate.h"

static std::vector<GUID> availableGUIDs;

Entity::Entity(const Vec2& pos, Sprite* sprite)
	:
	_sprite(sprite)
	, _id(nextId())
	, _object({{ pos, Vec2(0.2f, 0.2f) }, Vec2(0, 0)})
	, _conversation(nullptr)
	, _engaged(false)
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
	if (_conversation)
	{
		delete _conversation;
	}
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

void Entity::setConversation(Conversation* conversation)
{
	if (!conversation)
	{
		WARN("Could not add conversation to entity: " << _id << " - nullptr exception");
		return;
	}
	_conversation = conversation;
}

void Entity::update(GameState* gamestate)
{
	Collider::instance().push(&_object);
}

void Entity::engage(GameState* gamestate)
{
	_conversation->start();
	gamestate->setActiveConversation(_conversation);
	gamestate->setSubState(SUBSTATE_CONVERSATION);
}

void Entity::render(Renderer* renderer, const Camera* camera) const
{
	const Vec4& camPos = camera->getPos();
	Vec2 cam2DPos = Vec2(camPos.x, camPos.y);
	Vec4 pos(_object.location.pos.x, _object.location.pos.y, 0, 0);
	if (renderer && _sprite)
	{
		Renderable2D* renderable = Renderable2D::createRenderable2D(_sprite, Vec4(-camPos.x + pos.x, 
			-camPos.y + pos.y, camPos.z), 1.0f);
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
