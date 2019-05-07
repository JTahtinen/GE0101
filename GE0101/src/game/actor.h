#pragma once
#include "entity.h"

class Controller;

class Actor : public Entity
{
	Controller* _controller{ nullptr };
	std::vector<const Actor*>		_allies;
	std::vector<const Actor*>		_enemies;
	const Entity*					_target{ nullptr };
public:
	Actor(const Vec2& pos, Sprite* sprite, Controller* controller);
	Actor(const Vec2& pos, Sprite* sprite);
	Actor(const Vec2& pos);
	virtual ~Actor() override;
	void setController(Controller* controller);
	void setTarget(const Entity* target);
	const Entity* getTarget() const;
	void addAlly(const Actor* ally);
	void addEnemy(const Actor* enemy);
	virtual void update(Game* game) override;
};