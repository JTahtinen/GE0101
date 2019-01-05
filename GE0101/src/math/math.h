#pragma once

namespace math
{
	inline bool inBounds(float val, float floor, float ceil)
	{
		return (val >= floor && val < ceil);
	}

	inline bool inBounds(float xVal, float yVal, float xFloor, float yFloor, float xCeil, float yCeil)
	{
		return (inBounds(xVal, xFloor, xCeil) && inBounds(yVal, yFloor, yCeil));
	}
}