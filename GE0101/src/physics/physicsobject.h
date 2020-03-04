#pragma once
#include "../math/vec2.h"

class Game;

struct Position
{
	Vec2		center;
	Vec2		dimensions;
};

class PhysicsObject
{
	Position	_pos;
	Vec2		_force;
public:
	PhysicsObject(const Vec2& pos, const Vec2& dimensions);
	void setPos(const Vec2& pos);
	void setForce(const Vec2& force);
	void applyForce(const Vec2& force);
	void collisionCheck(const PhysicsObject& other);
	void update();
	bool isMoving() const { return _force.length() > 0.0f; }
	inline const Position& getPos() const { return _pos; }
	inline const Vec2& getForce() const { return _force; }
};