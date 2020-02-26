#pragma once
#include "entity.h"

class Controller;

class Actor : public Entity
{
	std::shared_ptr<Controller>						_controller{ nullptr };
	std::vector<std::shared_ptr<const Actor>>		_allies;
	std::vector<std::shared_ptr<const Actor>>		_enemies;
	std::shared_ptr<const Entity>					_target;
public:
	Actor(const Vec2& pos, std::vector<std::shared_ptr<const Sprite>> frames, std::shared_ptr<Controller> controller);
	Actor(const Vec2& pos, std::vector<std::shared_ptr<const Sprite>> frames);
	Actor(const Vec2& pos, std::shared_ptr<const Sprite> sprite, std::shared_ptr<Controller> controller);
	Actor(const Vec2& pos, std::shared_ptr<const Sprite> sprite);
	Actor(const Vec2& pos);
	virtual ~Actor() override;
	void setController(std::shared_ptr<Controller> controller);
	void setTarget(std::shared_ptr<const Entity> target);
	std::shared_ptr<const Entity> getTarget() const;
	void addAlly(std::shared_ptr<const Actor> ally);
	void addEnemy(std::shared_ptr<const Actor> enemy);
	virtual void update(GameState& gamestate) override;
};