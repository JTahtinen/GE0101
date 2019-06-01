#include "vec4.h"
#include <iostream>
#include "math.h"

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

Vec4::Vec4(float x, float y)
	: Vec4(x, y, 0.0f)
{
}

Vec4::Vec4()
	: Vec4(0.0f, 0.0f)
{
}


Vec4& Vec4::set(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
	return *this;
}

Vec4& Vec4::set(float x, float y, float z)
{
	return set(x, y, z, 0);
}

Vec4& Vec4::set(float x, float y)
{
	return set(x, y, 0);
}

Vec4 Vec4::getNormal() const
{
	float len = length();
	return Vec4(x / len, y / len, z / len, w / len);
}

Vec4& Vec4::normalize()
{
	float len = length();
	x /= len;
	y /= len;
	z /= len;
	w /= len;
	return *this;
}

float Vec4::length() const
{
	return sqrtf(x * x + y * y + z * z + w * w);
}

Vec4& Vec4::add(float x, float y, float z, float w)
{
	this->x += x;
	this->y += y;
	this->z += z;
	this->w += w;
	return *this;
}

Vec4& Vec4::add(const Vec4& other)
{
	return add(other.x, other.y, other.z, other.w);
}

Vec4& Vec4::sub(float x, float y, float z, float w)
{
	this->x -= x;
	this->y -= y;
	this->z -= z;
	this->w -= w;
	return *this;
}
Vec4& Vec4::Vec4::sub(const Vec4& other)
{
	return sub(other.x, other.y, other.z, other.w);
}
Vec4& Vec4::mul(float value)
{
	x *= value;
	y *= value;
	z *= value;
	w *= value;
	return *this;
}

Vec4 Vec4::operator+(const Vec4& other) const
{
	return Vec4(x + other.x, y + other.y, z + other.z, w + other.w);
}

Vec4 Vec4::operator-(const Vec4& other) const
{
	return Vec4(x - other.x, y - other.y, z - other.z, w - other.w);
}
Vec4 Vec4::operator*(float value) const
{
	return Vec4(x * value, y * value, z * value, w * value);
}


Vec4& Vec4::operator+=(const Vec4& other)
{
	return add(other);
}

Vec4& Vec4::operator-=(const Vec4& other)
{
	return sub(other);
}

Vec4& Vec4::operator*=(float value)
{
	return mul(value);
}
bool Vec4::operator==(const Vec4& other) const
{
	return (x == other.x && y == other.y && z == other.z && w == other.w);
}

bool Vec4::operator!=(const Vec4& other) const
{
	return !(*this == other);
}
bool Vec4::operator>(float distance) const
{
	return (length() > distance);
}
bool Vec4::operator<(float distance) const
{
	return (length() < distance);
}

bool Vec4::operator>=(float distance) const
{
	return (length() >= distance);
}

bool Vec4::operator<=(float distance) const
{
	return (length() <= distance);
}

Vec4 Vec4::operator-() const
{
	return Vec4(-x, -y, -z, -w);
}

void Vec4::print() const
{
	std::cout << toString() << std::endl;
}

std::string Vec4::toString() const
{
	return std::string("Vec4: [X: " + std::to_string(x) +
		", Y: " + std::to_string(y) +
		", W: " + std::to_string(z) +
		", Z: " + std::to_string(w) + "]");
}