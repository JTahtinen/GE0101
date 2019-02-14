#include "vec4.h"

Vec4::Vec4(float x, float y, float z, float w)
	:
	x(x)
	, y(y)
	, z(z)
	, w(w)
{
}

Vec4::Vec4(float x, float y, float z)
	: Vec4(x, y, z, 0.0f)
{
}

Vec4::Vec4()
	: Vec4(0.0f, 0.0f, 0.0f)
{
}