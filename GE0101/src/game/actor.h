#pragma once
#include "entity.h"

class Controller;

class Actor : public Entity
{
	const Controller* _controller{ nullptr };
public:
	Actor(const Vec2& pos, Sprite* sprite, Controller* controller);
	Actor(const Vec2& pos, Sprite* sprite);
	Actor(const Vec2& pos);
	Actor();
	void setController(const Controller* controller);
	virtual void update(Game* game) override;
};