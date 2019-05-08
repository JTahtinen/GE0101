#include "collider.h"
#include "../defs.h"
#include <math.h>
#include "../game/game.h"
Collider::Collider()
{
	_objects.reserve(100);
	_movingObjects.reserve(100);
}

bool Collider::overlap(const Location& loc1, const Location& loc2) const
{
	const Vec2& pos1 = loc1.pos;
	const Vec2& pos2 = loc2.pos;

	const Vec2& dim1 = loc1.dimensions;
	const Vec2& dim2 = loc2.dimensions;

	float halfC1W	= dim1.x / 2.0f;
	float halfC2W	= dim2.x / 2.0f;
	
	float halfC1H	= dim1.y / 2.0f;
	float halfC2H	= dim2.y / 2.0f;
	
	float left1		= (pos1.x - halfC1W);
	float left2		= (pos2.x - halfC2W);
	
	float right1	= (pos1.x + halfC1W);
	float right2	= (pos2.x + halfC2W);
	
	float bottom1	= (pos1.y - halfC1H);
	float bottom2	= (pos2.y - halfC2H);
	
	float top1		= (pos1.y + halfC1H);
	float top2		= (pos2.y + halfC2H);


	//TODO: Figure out why this hack is needed 

	bool xCollision = (left1 > left2 && left1 < right2 - 0.01f * Game::frameTime)
		|| (right1 < right2 && right1 > left2);

	bool yCollision = (bottom1 > bottom2 && bottom1 < top2 - 0.01f * Game::frameTime)
		|| (top1 < top2 && top1 > bottom2);


	return (xCollision && yCollision);
}

void Collider::update()
{
	for (auto& obj : _movingObjects)
	{
		const Vec2& force = obj->force;
		const Location& location = obj->location;
		const Vec2& pos = location.pos;
		const Vec2& dimensions = location.dimensions;
		const Vec2 nextPos = pos + force;
		const Location nextLocation = { nextPos, dimensions };
		Vec2 vel = force;
		for (auto& other : _objects)
		{
			if (obj == other) continue;
			
			const Location& otherLoc = other->location;
			if (overlap(nextLocation, otherLoc))
			{
				const Vec2& otherPos = otherLoc.pos;
				const Vec2& otherDim = otherLoc.dimensions;
				const Location nextXLoc = { Vec2(nextPos.x, pos.y), dimensions};
				const Location nextYLoc = { Vec2(pos.x, nextPos.y), dimensions};
				if (overlap(nextXLoc, otherLoc))
				{
					int dir;
					if (force.x > 0) dir = 1;
					else dir = -1;
					vel.x =
						-((pos.x - otherPos.x + dir * (dimensions.x / 2.0f))
							+ dir * (otherDim.x / 2.0f));
				}
			
				if (overlap(nextYLoc, otherLoc))
				{
					int dir;
					if (force.y > 0) dir = 1;
					else dir = -1;
					vel.y =
						-((pos.y - otherPos.y + dir * (dimensions.y / 2.0f))
							+ dir * (otherDim.y / 2.0f));
				}
		
				

				//TODO: Corner collision check
				break;
			}
		}
		obj->location.pos += vel;
	}
	clear();
}

void Collider::push(PhysicsObject* obj)
{
	_objects.push_back(obj);
	if (obj->force.length() > 0.0f)
	{
		_movingObjects.push_back(obj);
	}
}

void Collider::clear()
{
	_objects.clear();
	_movingObjects.clear();
}