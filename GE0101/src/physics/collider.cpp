#include "collider.h"
#include "../defs.h"
#include <math.h>
#include "../application/application.h"

bool physics::overlaps(const Position& loc1, const Position& loc2)
{
	// Margin needed because of floating point rounding error
	float errorMargin = 0.003f * Application::frametime;
	const Vec2& pos1 = loc1.center;
	const Vec2& pos2 = loc2.center;

	const Vec2& dim1 = loc1.dimensions;
	const Vec2& dim2 = loc2.dimensions;

	float halfC1W	= (dim1.x * 0.5f);
	float halfC2W	= (dim2.x * 0.5f);
	
	float halfC1H	= (dim1.y * 0.5f);
	float halfC2H	= (dim2.y * 0.5f);
	
	float left1		= (pos1.x - halfC1W);
	float left2		= (pos2.x - halfC2W);
	
	float right1	= (pos1.x + halfC1W);
	float right2	= (pos2.x + halfC2W);
	
	float bottom1	= (pos1.y - halfC1H);
	float bottom2	= (pos2.y - halfC2H);
	
	float top1		= (pos1.y + halfC1H);
	float top2		= (pos2.y + halfC2H);



	bool xCollision = (left1 > left2 && left1 < right2 - errorMargin)
		|| (right1 < right2 && right1 > left2 + errorMargin) || (left1 == left2) || (right1 == right2);

	bool yCollision = (bottom1 > bottom2 && bottom1 < top2 - errorMargin)
		|| (top1 < top2&& top1 > bottom2 + errorMargin) || (top1 == top2) || (bottom1 == bottom2);


	return (xCollision && yCollision);
}

