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
#include "components/staticgraphicscomponent.h"
#include "components/animatedgraphicscomponent.h"

static std::vector<GUID> availableGUIDs;

Entity::Entity(const Vec2& pos, std::vector<std::shared_ptr<const Sprite>> frames)
	: _id(nextId())
	, _object(pos, Vec2(0.07f, 0.19f))
	, _conversation(nullptr)
	, _engaged(false)
	, _graphics(std::make_shared<AnimatedGraphicsComponent>(frames))
{
}

Entity::Entity(const Vec2& pos, std::shared_ptr<const Sprite> sprite)
	:
	_sprite(sprite)
	, _id(nextId())
	, _object(pos, Vec2(0.07f, 0.19f))
	, _conversation(nullptr)
	, _engaged(false)
	, _graphics(std::make_shared<StaticGraphicsComponent>(sprite))
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


void Entity::setConversation(std::shared_ptr<Conversation> conversation)
{
	if (!conversation)
	{
		WARN("Could not add conversation to entity: " << _id << " - nullptr exception");
		return;
	}
	_conversation = conversation;
}

void Entity::update(GameState& gamestate)
{
	auto& entities = gamestate.getEntities();
	for (auto& entity : entities)
	{
		_object.collisionCheck(*entity->getPhysics());
	}
	gamestate.getMap()->collisionCheck(*this);
	_object.update();
	_graphics->update(this);
}

void Entity::engage(GameState& gamestate)
{
	if (_conversation)
	{
		_conversation->start();
		// Temp code
		gamestate.setActiveConversation(_conversation);
		gamestate.setSubState(SUBSTATE_CONVERSATION);
	}
}

void Entity::render(Layer& layer, const Camera& camera) const
{
	_graphics->render(this, &layer, camera);
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
