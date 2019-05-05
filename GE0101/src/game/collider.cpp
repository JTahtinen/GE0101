#include "collider.h"
#include "../defs.h"

Collider::Collider(float width, float height)
	: _dimensions({ width, height })
{
}

bool Collider::collidesWith(const Vec2& pos1, const Vec2& pos2,
	const Collider& collider1, const Collider& collider2)
{
	float halfC1W = collider1._dimensions.w / 2.0f;
	float halfC2W = collider2._dimensions.w / 2.0f;

	float halfC1H = collider1._dimensions.h / 2.0f;
	float halfC2H = collider2._dimensions.h / 2.0f;
	
	float left1 = pos1.x - halfC1W;
	float left2 = pos2.x - halfC2W;

	float right1 = pos1.x + halfC1W;
	float right2 = pos2.x + halfC2W;

	float bottom1 = pos1.y - halfC1H;
	float bottom2 = pos2.y - halfC2H;

	float top1 = pos1.y + halfC1H;
	float top2 = pos2.y + halfC2H;

	bool xCollision = (left1 > left2 && left1 < right2)
		|| (right1 < right2 && right1 > left2);
	bool yCollision = (bottom1 > bottom2 && bottom1 < top2)
		|| (top1 < top2 && top1 > bottom2);


	return (xCollision && yCollision);
}