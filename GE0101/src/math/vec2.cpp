#include "vec2.h"
#include "math.h"

Vec2::Vec2(float x, float y)
	: x(x)
	, y(y)
{
}

float Vec2::length() const
{
	return sqrtf(x * x + y * y);
}

Vec2 Vec2::getNormal() const
{
	float len = length();
	if (len != 0)
	{
		return Vec2(x / len, y / len);
	}
	return Vec2();
}

void Vec2::add(float x, float y)
{
	this->x += x;
	this->y += y;
}

void Vec2::add(const Vec2& other)
{
	add(other.x, other.y);
}

void Vec2::sub(float x, float y)
{
	this->x -= x;
	this->y -= y;
}

void Vec2::sub(const Vec2& other)
{
	sub(other.x, other.y);
}

void Vec2::mul(float value)
{
	x *= value;
	y *= value;
}

float Vec2::dot(const Vec2& other)
{
	return x * other.x + y * other.y;
}
