#include "vec2.h"
#include "math.h"
#include "../defs.h"

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

float Vec2::dot(const Vec2& other) const
{
	return x * other.x + y * other.y;
}

Vec2& Vec2::setToAbs()
{
	if (x < 0.0f)
	{
		x = -x;
	}
	if (y < 0.0f)
	{
		y = -y;
	}
	return *this;
}

Vec2 Vec2::operator+(const Vec2& other) const
{
	return Vec2(x + other.x, y + other.y);
}

Vec2 Vec2::operator-(const Vec2& other) const
{
	return Vec2(x - other.x, y - other.y);
}

Vec2 Vec2::operator*(float value) const
{
	return Vec2(x * value, y * value);
}

float Vec2::operator*(const Vec2& other) const
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

bool Vec2::operator==(const Vec2& other) const
{
	return (x == other.x && y == other.y);
}

bool Vec2::operator!=(const Vec2& other) const
{
	return !(*this == other);
}

bool Vec2::operator>(float distance) const
{
	return (length() > distance);
}

bool Vec2::operator<(float distance) const
{
	return (length() < distance);
}

bool Vec2::operator>=(float distance) const
{
	float len = length();
	return (len > distance || len == distance);
}

bool Vec2::operator<=(float distance) const
{
	float len = length();
	return (len < distance || len == distance);
}

Vec2 Vec2::operator-() const
{
	return Vec2(-x, -y);
}

void Vec2::print() const
{
	MSG(toString());
}

std::string Vec2::toString() const
{
	return "Vec2( X : " + std::to_string(x) + ", Y: " + std::to_string(y) + " )";
}