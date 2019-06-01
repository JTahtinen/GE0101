#include "actor.h"
#include "controllers/controller.h"

Actor::Actor(const Vec2& pos, Sprite* sprite, Controller* controller)
	:
	Entity(pos, sprite)
	, _controller(controller)
{
}

Actor::Actor(const Vec2& pos, Sprite* sprite)
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
	delete _controller;
	_controller = nullptr;
}

void Actor::setController(Controller* controller)
{
	_controller = controller;
}

void Actor::setTarget(const Entity* target)
{
	_target = target;
}

const Entity* Actor::getTarget() const
{
	return _target;
}

void Actor::addAlly(const Actor* ally)
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

void Actor::addEnemy(const Actor* enemy)
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

void Actor::update(GameState* gamestate)
{
	setForce(Vec2(0, 0));

	if (_controller)
	{
		_controller->update(this);
	}
	Entity::update(gamestate);
}