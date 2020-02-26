#include "actor.h"
#include "controllers/controller.h"

Actor::Actor(const Vec2& pos, std::vector<std::shared_ptr<const Sprite>> frames, std::shared_ptr<Controller> controller)
	: 
	Entity(pos, frames)
	, _controller(controller)
{
}

Actor::Actor(const Vec2& pos, std::vector<std::shared_ptr<const Sprite>> frames)
	: 
	Actor(pos, frames, nullptr)
{
}

Actor::Actor(const Vec2& pos, std::shared_ptr<const Sprite> sprite, std::shared_ptr<Controller> controller)
	:
	Entity(pos, sprite)
	, _controller(controller)
{
}

Actor::Actor(const Vec2& pos, std::shared_ptr<const Sprite> sprite)
	: 
	Actor(pos, sprite, nullptr)
{
}

Actor::Actor(const Vec2& pos)
	:
	Actor(pos, nullptr)
{
}

Actor::~Actor()
{
}

void Actor::setController(std::shared_ptr<Controller> controller)
{
	_controller = controller;
}

void Actor::setTarget(std::shared_ptr<const Entity> target)
{
	_target = target;
}

std::shared_ptr<const Entity> Actor::getTarget() const
{
	return _target;
}

void Actor::addAlly(std::shared_ptr<const Actor> ally)
{
	if (ally)
	{
		for (const auto& actor : _allies)
		{
			if (ally == actor)
			{
				return;
			}
		}
		_allies.push_back(ally);
	}
}

void Actor::addEnemy(std::shared_ptr<const Actor> enemy)
{
	if (enemy)
	{
		for (const auto& actor : _enemies)
		{
			if (enemy == actor)
			{
				return;
			}
		}
		_enemies.push_back(enemy);
	}
}

void Actor::update(GameState& gamestate)
{
	stopMoving();

	if (_controller)
	{
		_controller->update(this);
	}
	Entity::update(gamestate);
}