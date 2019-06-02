#include "entity.h"
#include <iostream>
#include <vector>
#include "../../globals.h"
#include "../../input/input.h"
#include "../camera.h"
#include "../game.h"
#include "../../physics/collider.h"
#include "../../defs.h"
#include "../states/gamestate.h"

static std::vector<GUID> availableGUIDs;

Entity::Entity(const Vec2& pos, Sprite* sprite)
	:
	_sprite(sprite)
	, _id(nextId())
	, _object(pos, Vec2(0.07f, 0.19f))
	, _conversation(nullptr)
	, _engaged(false)
{
#ifdef _DEBUG
	MSG("Created Entity GUID: " << _id);
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
	MSG("Deleted Entity GUID: " << _id);
#endif
}

void Entity::move(const Vec2& dir, float amt)
{
	_object.applyForce(dir.getNormal() * amt);
}

void Entity::stopMoving()
{
	_object.setForce(Vec2(0, 0));
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
	auto& entities = gamestate->getEntities();
	for (auto& entity : entities)
	{
		_object.collisionCheck(*entity->getPhysics());
	}
	gamestate->getMap()->collisionCheck(this);
	_object.update();
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
	const Vec2& objPos = _object.getPos().center;
	Vec4 pos(objPos.x, objPos.y, 0, 0);
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
