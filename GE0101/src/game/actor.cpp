#include "actor.h"
#include "controller.h"

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

void Actor::setController(const Controller* controller)
{
	_controller = controller;
}

void Actor::update(Game* game)
{
	setVel(Vec2(0, 0));

	if (_controller)
	{
		_controller->update(this);
	}
	Entity::update(game);
}