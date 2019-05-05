#pragma once
#include "actor.h"
#include <vector>

class NPC : public Actor
{
	std::vector<const Actor*>		_allies;
	std::vector<const Actor*>		_enemies;
	const Entity*					_target{ nullptr };
public:
	using Actor::Actor;
	void setTarget(const Entity* target);
	const Entity* getTarget() const;
	void addAlly(const Actor* ally);
	void addEnemy(const Actor* enemy);
};