#include "vec2.h"
#include "math.h"

Vec2::Vec2(float x, float y)
	: x(x)
	, y(y)
{
}

Vec2& Vec2::set(float x, float y)
{
	this->x = x;
	this->y = y;
	return *this;
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

Vec2& Vec2::normalize()
{
	float len = length();
	if (len != 0)
	{
		x /= len;
		y /= len;
	}
	return *this;
}

Vec2& Vec2::add(float x, float y)
{
	this->x += x;
	this->y += y;
	return *this;
}

Vec2& Vec2::add(const Vec2& other)
{
	add(other.x, other.y);
	return *this;
}

Vec2& Vec2::sub(float x, float y)
{
	this->x -= x;
	this->y -= y;
	return *this;
}

Vec2& Vec2::sub(const Vec2& other)
{
	sub(other.x, other.y);
	return *this;
}

Vec2& Vec2::mul(float value)
{
	x *= value;
	y *= value;
	return *this;
}

float Vec2::dot(const Vec2& other)
{
	return x * other.x + y * other.y;
}

Vec2 Vec2::operator+(const Vec2& other)
{
	return Vec2(x + other.x, y + other.y);
}

Vec2 Vec2::operator-(const Vec2& other)
{
	return Vec2(x - other.x, y - other.y);
}

Vec2 Vec2::operator*(float value)
{
	return Vec2(x * value, y * value);
}

float Vec2::operator*(const Vec2& other)
{
	return dot(other);
}

Vec2& Vec2::operator+=(const Vec2& other)
{
	x += other.x;
	y += other.y;
	return *this;
}

Vec2& Vec2::operator-=(const Vec2& other)
{
	x -= other.x;
	y -= other.y;
	return *this;
}

Vec2& Vec2::operator*=(float value)
{
	x *= value;
	y *= value;
	return *this;
}

bool Vec2::operator==(const Vec2& other)
{
	return (x == other.x && y == other.y);
}

bool Vec2::operator!=(const Vec2& other)
{
	return !(*this == other);
}
