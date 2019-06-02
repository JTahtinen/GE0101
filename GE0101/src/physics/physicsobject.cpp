#include "physicsobject.h"
#include "../game/states/gamestate.h"
#include "collider.h"
#include "../game/game.h"

PhysicsObject::PhysicsObject(const Vec2& pos, const Vec2& dimensions)
	: _pos({ pos, dimensions })
{
}

void PhysicsObject::setPos(const Vec2& pos)
{
	_pos.center = pos;
}

void PhysicsObject::setForce(const Vec2& force)
{
	_force = force * Game::frameTime;
}

void PhysicsObject::applyForce(const Vec2& force)
{
	_force += force * Game::frameTime;
}

void PhysicsObject::collisionCheck(const PhysicsObject& other)
{
	const Vec2& pos = _pos.center;
	Vec2 vel = _force;
	if (this->isMoving())
	{
		const Vec2& dimensions = _pos.dimensions;


		if (&other == this) return;
		const Vec2 nextPos = pos + vel;
		const Position nextLocation = { nextPos, dimensions };

		const Position& otherLoc = other.getPos();
		if (physics::overlaps(nextLocation, otherLoc))
		{
			bool xCollision = false;
			bool yCollision = false;
			//collisionHappened = true;
			const Vec2& otherPos = otherLoc.center;
			const Vec2& otherDim = otherLoc.dimensions;
			const Position nextXLoc = { Vec2(nextPos.x, pos.y), dimensions };
			const Position nextYLoc = { Vec2(pos.x, nextPos.y), dimensions };
			if (physics::overlaps(nextXLoc, otherLoc))
			{
				int dir;
				if (vel.x > 0) dir = 1;
				else dir = -1;
				vel.x =
					-((pos.x - otherPos.x + dir * (dimensions.x * 0.5f))
						+ dir * (otherDim.x * 0.5f));
				xCollision = true;
			}

			if (physics::overlaps(nextYLoc, otherLoc))
			{
				int dir;
				if (vel.y > 0) dir = 1;
				else dir = -1;
				vel.y =
					-((pos.y - otherPos.y + dir * (dimensions.y * 0.5f))
						+ dir * (otherDim.y * 0.5f));
				yCollision = true;
			}



			//TODO: Corner collision check
			//break;
		}
	}

	_force = vel;
}

void PhysicsObject::update()
{
	_pos.center += _force;
}
