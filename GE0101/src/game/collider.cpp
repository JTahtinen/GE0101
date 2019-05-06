#include "collider.h"
#include "../defs.h"
#include "game.h"
#include "entity.h"
#include <math.h>

Collider::Collider(float width, float height)
	: _dimensions({ width, height })
{
}

bool Collider::collidesWith(const Vec2& pos1, const Vec2& pos2,
	const Collider& collider1, const Collider& collider2)
{
	float halfC1W	= collider1._dimensions.w / 2.0f;
	float halfC2W	= collider2._dimensions.w / 2.0f;

	float halfC1H	= collider1._dimensions.h / 2.0f;
	float halfC2H	= collider2._dimensions.h / 2.0f;
	
	float left1		= (pos1.x - halfC1W);
	float left2		= (pos2.x - halfC2W);

	float right1	= (pos1.x + halfC1W);
	float right2	= (pos2.x + halfC2W);

	float bottom1	= (pos1.y - halfC1H);
	float bottom2	= (pos2.y - halfC2H);

	float top1		= (pos1.y + halfC1H);
	float top2		= (pos2.y + halfC2H);


	//TODO: Figure out why this hack is needed 

	bool xCollision = (left1 > left2 && left1 < right2 - 0.01f)
		|| (right1 < right2 && right1 > left2);

	bool yCollision = (bottom1 > bottom2 && bottom1 < top2 - 0.01f)
		|| (top1 < top2 && top1 > bottom2);


	return (xCollision && yCollision);
}

Vec2 Collider::clippedVelocityVector(const Game* game, const Entity* e)
{
	const Vec2& pos = e->getPos();
	const Vec2& vel = e->getVel();
	const Collider& collider = *e->getCollider();
	auto& entities = game->getEntities();
	const Vec2 nextPos = pos + vel;

	for (auto& entity : entities)
	{
		if (entity == e) continue;
		const Vec2& otherPos = entity->getPos();
		const Collider& otherCollider = *entity->getCollider();
		if (collidesWith(nextPos, otherPos, collider, otherCollider))
		{
			Vec2 nextXPos = Vec2(nextPos.x, pos.y);
			Vec2 nextYPos = Vec2(pos.x, nextPos.y);
			Vec2 clippedVel;
			if (collidesWith(nextXPos, otherPos, collider, otherCollider))
			{
				int dir;
				if (vel.x > 0) dir = 1;
				else dir = -1;
				clippedVel.x = 
					 -((pos.x - otherPos.x + dir * (collider._dimensions.w / 2.0f))
					+ dir * (otherCollider._dimensions.w / 2.0f));
			}
			else 
			{
				clippedVel.x = vel.x;
			}

			if (collidesWith(nextYPos, otherPos, collider, otherCollider))
			{
				int dir;
				if (vel.y > 0) dir = 1;
				else dir = -1;
				clippedVel.y = 
					-((pos.y - otherPos.y + dir * (collider._dimensions.h / 2.0f)) 
					+ dir * (otherCollider._dimensions.h / 2.0f));
			} 
			else
			{
				clippedVel.y = vel.y;
			}
	
			return clippedVel;
		}
	}
	return vel;
}